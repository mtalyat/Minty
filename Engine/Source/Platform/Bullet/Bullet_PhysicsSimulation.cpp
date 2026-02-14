#include "pch.h"
#include "Bullet_PhysicsSimulation.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_Physics.h"
#include "Platform/Bullet/Bullet_RigidBody.h"
#include "Platform/Bullet/Bullet_Object.h"
#include "Minty/Physics/PhysicsSimulationInfo.h"
#include "Minty/Physics/RaycastHit.h"
#include "Minty/Physics/CollisionData.h"
#ifdef MINTY_DEBUG
#include "Minty/Scene/Scene.h"
#include "Minty/Scene/SceneManager.h"
#include "Minty/Entity/EntityManager.h"
#endif // MINTY_DEBUG

using namespace Minty;

Minty::Bullet_PhysicsSimulation::Bullet_PhysicsSimulation(PhysicsSimulationInfo const &info)
	: PhysicsSimulation(info), mp_broadphase(new btDbvtBroadphase()), mp_collisionConfiguration(new btDefaultCollisionConfiguration()), mp_dispatcher(new btCollisionDispatcher(mp_collisionConfiguration)), mp_solver(new btSequentialImpulseConstraintSolver()), mp_dynamicsWorld(new btDiscreteDynamicsWorld(mp_dispatcher, mp_broadphase, mp_solver, mp_collisionConfiguration)), m_previousCollisions(), m_currentCollisions()
{
	// set gravity
	set_gravity(info.gravity);
}

Minty::Bullet_PhysicsSimulation::~Bullet_PhysicsSimulation()
{
	delete mp_dynamicsWorld;
	delete mp_solver;
	delete mp_dispatcher;
	delete mp_collisionConfiguration;
	delete mp_broadphase;
}

Size Minty::Bullet_PhysicsSimulation::get_size() const
{
	return static_cast<Size>(mp_dynamicsWorld->getNumCollisionObjects());
}

void Minty::Bullet_PhysicsSimulation::set_gravity(Float3 const &gravity)
{
	// set the gravity in the dynamics world
	mp_dynamicsWorld->setGravity(Bullet_Physics::to_bullet(gravity));

	PhysicsSimulation::set_gravity(gravity);
}

void Minty::Bullet_PhysicsSimulation::step(Float const elapsedTime)
{
	mp_dynamicsWorld->stepSimulation(elapsedTime, 1, elapsedTime);

	// check for collision events
	btDispatcher *dispatcher = mp_dynamicsWorld->getDispatcher();
	int const numManifolds = dispatcher->getNumManifolds();

	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold *const contactManifold = dispatcher->getManifoldByIndexInternal(i);
		Int const numContacts = contactManifold->getNumContacts();

		// skip if no actual contact points (stale/persistent manifold)
		if (numContacts == 0)
		{
			continue;
		}

		// get the two collision objects
		btCollisionObject const *const objA = contactManifold->getBody0();
		btCollisionObject const *const objB = contactManifold->getBody1();

		// ignore if both are static
		if (objA->isStaticObject() && objB->isStaticObject())
		{
			continue;
		}

		// get the user data
		Bullet_Object *const objectDataA = static_cast<Bullet_Object *>(objA->getUserPointer());
		MINTY_ASSERT(objectDataA != nullptr, ErrorCode::InvalidUserData);
		Entity const entityA = objectDataA->entity;

		Bullet_Object *const objectDataB = static_cast<Bullet_Object *>(objB->getUserPointer());
		MINTY_ASSERT(objectDataB != nullptr, ErrorCode::InvalidUserData);
		Entity const entityB = objectDataB->entity;

		// check if these objects should collide based on layer masks
		Layer const layerBitA = objectDataA->layerBit;
		Layer const layerBitB = objectDataB->layerBit;
		if ((objectDataA->layerMask & layerBitB) == 0 || (objectDataB->layerMask & layerBitA) == 0)
		{
			// these layers should not collide, skip callbacks
			continue;
		}

		// TODO: determine how to handle multiple contact points properly
		btManifoldPoint const &pt = contactManifold->getContactPoint(0);
		Float3 const point = Bullet_Physics::to_minty(pt.getPositionWorldOnA());
		Float3 const otherPoint = Bullet_Physics::to_minty(pt.getPositionWorldOnB());
		Float3 const normal = Bullet_Physics::to_minty(pt.m_normalWorldOnB);
		Float const distance = pt.getDistance();

		// get the collision data
		CollisionData collisionDataA{};
		collisionDataA.entity = entityA;
		collisionDataA.otherEntity = entityB;
		collisionDataA.point = point;
		collisionDataA.otherPoint = otherPoint;
		collisionDataA.normal = normal;
		collisionDataA.distance = distance;

		CollisionData collisionDataB{};
		collisionDataB.entity = entityB;
		collisionDataB.otherEntity = entityA;
		collisionDataB.point = otherPoint;
		collisionDataB.otherPoint = point;
		collisionDataB.normal = -normal;
		collisionDataB.distance = distance;

		// get the collision type
		CollisionPair const collisionPair = CollisionPair(objectDataA, objectDataB);
		Bool const newCollision = !m_previousCollisions.contains(collisionPair);

		if (newCollision)
		{
			// new collision
			if (objectDataA->collider != nullptr)
			{
				objectDataA->collider->invoke_on_enter(collisionDataA);
			}
			if (objectDataB->collider != nullptr)
			{
				objectDataB->collider->invoke_on_enter(collisionDataB);
			}
			m_currentCollisions.add(collisionPair);
		}
		else
		{
			// ongoing collision
			if (objectDataA->collider != nullptr)
			{
				objectDataA->collider->invoke_on_stay(collisionDataA);
			}
			if (objectDataB->collider != nullptr)
			{
				objectDataB->collider->invoke_on_stay(collisionDataB);
			}
			m_currentCollisions.add(collisionPair);
		}
	}

	// check for ended collisions
	for (CollisionPair const &previousCollision : m_previousCollisions)
	{
		if (!m_currentCollisions.contains(previousCollision))
		{
			// collision ended
			Bullet_Object *const objectDataA = static_cast<Bullet_Object *>(const_cast<void *>(previousCollision.a));
			MINTY_ASSERT(objectDataA != nullptr, ErrorCode::InvalidUserData);
			Entity const entityA = objectDataA->entity;

			Bullet_Object *const objectDataB = static_cast<Bullet_Object *>(const_cast<void *>(previousCollision.b));
			MINTY_ASSERT(objectDataB != nullptr, ErrorCode::InvalidUserData);
			Entity const entityB = objectDataB->entity;

			CollisionData collisionDataA{};
			collisionDataA.entity = entityA;
			collisionDataA.otherEntity = entityB;

			CollisionData collisionDataB{};
			collisionDataB.entity = entityB;
			collisionDataB.otherEntity = entityA;

			if (objectDataA->collider != nullptr)
			{
				objectDataA->collider->invoke_on_exit(collisionDataA);
			}
			if (objectDataB->collider != nullptr)
			{
				objectDataB->collider->invoke_on_exit(collisionDataB);
			}
		}
	}

	// move current collisions to previous for next step
	m_previousCollisions = std::move(m_currentCollisions);
	m_currentCollisions.clear();
}

void Minty::Bullet_PhysicsSimulation::add_static(Entity const entity, Transform const &transform, Collider &collider, Layer const layer, Layer const layerMask)
{
	// get data
	Bullet_Collider &btCollider = static_cast<Bullet_Collider &>(collider);

	// update the transform
	btCollider.set_transform(transform);

	// add the collision object to the dynamics world
	btCollisionObject *const collisionObject = btCollider.get_collision_object();
	mp_dynamicsWorld->addCollisionObject(collisionObject, LayerManager::layer_to_bit(layer), layerMask);

	// update the user data
	Bullet_Object *const objectData = static_cast<Bullet_Object *>(collisionObject->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::InvalidUserData);
	objectData->entity = entity;
	objectData->collider = &collider;
	objectData->layerBit = LayerManager::layer_to_bit(layer);
	objectData->layerMask = layerMask;

#ifdef MINTY_DEBUG

	SceneManager &sceneManager = SceneManager::get_singleton();
	Ref<Scene> const &scene = sceneManager.get_active();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();
	MINTY_LOG_DEBUG_F("Added static Collider from simulation: {}", entityManager.to_string(objectData->entity));

#endif // MINTY_DEBUG
}

void Minty::Bullet_PhysicsSimulation::add_dynamic(Entity const entity, RigidBody &body, Layer const layer, Layer const layerMask)
{
	LayerManager &layerManager = LayerManager::get_singleton();

	// get data
	btRigidBody *const rigidBody = static_cast<btRigidBody *>(body.get_native());

	// add the rigid body to the dynamics world
	mp_dynamicsWorld->addRigidBody(rigidBody, LayerManager::layer_to_bit(layer), layerMask);

	// update the user data
	Bullet_Object *const objectData = static_cast<Bullet_Object *>(rigidBody->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::InvalidUserData);
	objectData->entity = entity;
	objectData->collider = body.get_collider().get();
	objectData->layerBit = layerManager.layer_to_bit(layer);
	objectData->layerMask = layerMask;

#ifdef MINTY_DEBUG

	SceneManager &sceneManager = SceneManager::get_singleton();
	Ref<Scene> const &scene = sceneManager.get_active();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();
	MINTY_LOG_DEBUG_F("Added dynamic RigidBody to simulation: {} / {}", entityManager.to_string(objectData->entity), objectData->collider->get_position());

#endif // MINTY_DEBUG
}

void Minty::Bullet_PhysicsSimulation::remove_static(Collider &collider)
{
	// remove from collisions
	btCollisionObject *const collisionObject = static_cast<btCollisionObject *>(collider.get_native());
	MINTY_ASSERT(collisionObject != nullptr, ErrorCode::Argument_KeyNotFound);
	Bullet_Object *const objectData = static_cast<Bullet_Object *>(collisionObject->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::InvalidUserData);
	remove_collisions_for_object(objectData);

	// remove from dynamics world
	mp_dynamicsWorld->removeCollisionObject(collisionObject);

#ifdef MINTY_DEBUG

	SceneManager &sceneManager = SceneManager::get_singleton();
	Ref<Scene> const &scene = sceneManager.get_active();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();
	MINTY_LOG_DEBUG_F("Removed static Collider from simulation: {}", entityManager.to_string(objectData->entity));

#endif // MINTY_DEBUG

	// clear user data
	objectData->entity = INVALID_ENTITY;
	objectData->collider = nullptr;
}

void Minty::Bullet_PhysicsSimulation::remove_dynamic(RigidBody &body)
{
	// remove from collisions
	btRigidBody *const rigidBody = static_cast<btRigidBody *>(body.get_native());
	Bullet_Object *const objectData = static_cast<Bullet_Object *>(rigidBody->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::InvalidUserData);
	remove_collisions_for_object(objectData);

	// remove from dynamics world
	mp_dynamicsWorld->removeRigidBody(rigidBody);

#ifdef MINTY_DEBUG

	SceneManager &sceneManager = SceneManager::get_singleton();
	Ref<Scene> const &scene = sceneManager.get_active();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();
	MINTY_LOG_DEBUG_F("Removed dynamic RigidBody from simulation: {}", entityManager.to_string(objectData->entity));

#endif // MINTY_DEBUG

	// clear user data
	objectData->entity = INVALID_ENTITY;
	objectData->collider = nullptr;
	objectData->layerBit = 0;
	objectData->layerMask = 0;
}

Bool Minty::Bullet_PhysicsSimulation::raycast(Float3 const &origin, Float3 const &direction, RaycastHit &hit, Layer const layer, Layer const layerMask, Float const maxDistance) const
{
	// if too small of a distance, nothing is going to be hit
	if (maxDistance <= Math::EPSILON)
	{
		return false;
	}

	// if the direction is zero, nothing is going to be hit
	if (direction == Math::ZERO)
	{
		return false;
	}

	// create the ray
	btVector3 btOrigin = Bullet_Physics::to_bullet(origin);
	btVector3 btDirection = Bullet_Physics::to_bullet(direction);
	btVector3 btEnd = btOrigin + (btDirection.normalized() * maxDistance);

	// create the raycast
	btCollisionWorld::ClosestRayResultCallback rayCallback(btOrigin, btEnd);
	rayCallback.m_collisionFilterGroup = LayerManager::layer_to_bit(layer);
	rayCallback.m_collisionFilterMask = static_cast<int>(layerMask);

	// perform the raycast
	mp_dynamicsWorld->rayTest(btOrigin, btEnd, rayCallback);

	// check if we hit something
	if (rayCallback.hasHit())
	{
		// get the user data
		Bullet_Object *objectData = static_cast<Bullet_Object *>(rayCallback.m_collisionObject->getUserPointer());
		MINTY_ASSERT(objectData != nullptr, ErrorCode::InvalidUserData);

		// populate the hit information
		hit.point = Bullet_Physics::to_minty(rayCallback.m_hitPointWorld);
		hit.normal = Bullet_Physics::to_minty(rayCallback.m_hitNormalWorld);
		hit.distance = Math::magnitude(hit.point - origin);
		hit.entity = objectData->entity;
		return true;
	}
	return false;
}

void Minty::Bullet_PhysicsSimulation::clear()
{
	// clear the dynamics world
	Int count = mp_dynamicsWorld->getNumCollisionObjects();
	for (Int i = count - 1; i >= 0; i--)
	{
		// deleting handled by the individual objects
		btCollisionObject *obj = mp_dynamicsWorld->getCollisionObjectArray()[i];
		mp_dynamicsWorld->removeCollisionObject(obj);
	}
}

void Minty::Bullet_PhysicsSimulation::remove_collisions_for_object(AnyConst object)
{
	Vector<CollisionPair> collisionsToRemove(m_previousCollisions.get_size());
	for (CollisionPair const &collision : m_previousCollisions)
	{
		if (collision.contains(object))
		{
			collisionsToRemove.add(collision);
		}
	}
	for (CollisionPair const &collision : collisionsToRemove)
	{
		m_previousCollisions.remove(collision);
	}
}
