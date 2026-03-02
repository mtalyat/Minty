#include "pch.h"
#include "Bullet_PhysicsSimulation.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_Physics.h"
#include "Platform/Bullet/Bullet_Rigidbody.h"
#include "Platform/Bullet/Bullet_Object.h"
#include "Minty/Physics/PhysicsSimulationInfo.h"
#include "Minty/Physics/RaycastHit.h"
#include "Minty/Physics/CollisionData.h"
#ifdef MINTY_DEBUG
#include "Minty/Scene/Scene.h"
#include "Minty/Scene/SceneManager.h"
#include "Minty/Entity/EntityManager.h"
#endif // MINTY_DEBUG

// NOTE: Bullet must use new and delete, as those have been overridden to use its own custom aligned allocator

using namespace Minty;

Minty::Bullet_PhysicsSimulation::Bullet_PhysicsSimulation(PhysicsSimulationInfo const &info)
	: PhysicsSimulation(info), mp_broadphase(nullptr), mp_collisionConfiguration(nullptr), mp_dispatcher(nullptr), mp_solver(nullptr), mp_dynamicsWorld(nullptr), m_entityToObjectData(), m_previousCollisions(), m_currentCollisions()
{
	// initialize bullet
	mp_broadphase = new btDbvtBroadphase();
	mp_collisionConfiguration = new btDefaultCollisionConfiguration();
	mp_dispatcher = new btCollisionDispatcher(mp_collisionConfiguration);
	mp_solver = new btSequentialImpulseConstraintSolver();
	mp_dynamicsWorld = new btDiscreteDynamicsWorld(mp_dispatcher, mp_broadphase, mp_solver, mp_collisionConfiguration);

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
		MINTY_ASSERT(m_entityToObjectData.contains(entityA) && m_entityToObjectData.at(entityA).isInSimulation, ErrorCode::Object_InvalidState);

		Bullet_Object *const objectDataB = static_cast<Bullet_Object *>(objB->getUserPointer());
		MINTY_ASSERT(objectDataB != nullptr, ErrorCode::InvalidUserData);
		Entity const entityB = objectDataB->entity;
		MINTY_ASSERT(m_entityToObjectData.contains(entityB) && m_entityToObjectData.at(entityB).isInSimulation, ErrorCode::Object_InvalidState);

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

void Minty::Bullet_PhysicsSimulation::register_entity(Entity const entity, Layer const layer, Layer const layerMask, Collider &collider, Transform const& transform)
{
	// register the entity, leave the rest for later
	register_entity(entity, layer, layerMask);

	// register the collider
	EntityObjectData &entityData = m_entityToObjectData.at(entity);

	// get the collision shape
	Bullet_Collider &btCollider = static_cast<Bullet_Collider &>(collider);
	btCollisionShape *const collisionShape = btCollider.get_collision_shape();

	// create the collision object and bind it
	btTransform btTransform = btTransform::getIdentity();
	btTransform.setOrigin(Bullet_Physics::to_bullet(transform.get_local_position()));
	btTransform.setRotation(Bullet_Physics::to_bullet(transform.get_local_rotation()));
	btCollisionObject *collisionObject = new btCollisionObject();
	collisionObject->setUserPointer(entityData.data);
	collisionObject->setCollisionShape(collisionShape);
	collisionObject->setWorldTransform(btTransform);
	btCollider.bind_collision_object(collisionObject);

	// update the entity's object data
	entityData.object = collisionObject;
	Bullet_Object *const objectData = entityData.data;
	objectData->collider = &collider;
}

void Minty::Bullet_PhysicsSimulation::register_entity(Entity const entity, Layer const layer, Layer const layerMask, Collider &collider, Rigidbody &rigidbody)
{
	// register the entity, leave the rest for later
	register_entity(entity, layer, layerMask);

	// register the collider and rigidbody
	EntityObjectData &entityData = m_entityToObjectData.at(entity);

	// get the collision shape
	Bullet_Collider &btCollider = static_cast<Bullet_Collider &>(collider);
	btCollisionShape *const collisionShape = btCollider.get_collision_shape();

	// create the rigidbody and bind it
	Float const mass = rigidbody.get_mass();
	btTransform btTransform = btTransform::getIdentity();
	btVector3 inertia(0, 0, 0);
	if (mass > 0.0f)
	{
		collisionShape->calculateLocalInertia(mass, inertia);
	}
	btMotionState *const motionState = new btDefaultMotionState(btTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, inertia);
	btRigidBody *const rigidbodyObject = new btRigidBody(rbInfo);
	rigidbodyObject->setUserPointer(entityData.data);
	rigidbodyObject->setWorldTransform(btTransform);
	Bullet_Rigidbody &btRigidbody = static_cast<Bullet_Rigidbody &>(rigidbody);
	btRigidbody.bind_rigidbody(rigidbodyObject);

	// bind the body to the collider as well
	btCollider.bind_collision_object(rigidbodyObject);

	// update the entity's object data
	entityData.body = rigidbodyObject;
	Bullet_Object *const objectData = entityData.data;
	objectData->collider = &collider;
	objectData->rigidbody = &rigidbody;
}

void Minty::Bullet_PhysicsSimulation::register_entity(Entity const entity, Layer const layer, Layer const layerMask)
{
	// ensure not already registered
	MINTY_ASSERT(!m_entityToObjectData.contains(entity), ErrorCode::Argument_KeyAlreadyExists);

	// create the object data
	Bullet_Object *const objectData = new Bullet_Object();
	objectData->entity = entity;
	objectData->layerBit = LayerManager::layer_to_bit(layer);
	objectData->layerMask = layerMask;

	// add to map for easy lookup on addition
	m_entityToObjectData.add(entity, EntityObjectData{objectData, nullptr, nullptr, false});
}

void Minty::Bullet_PhysicsSimulation::unregister_entity(Entity const entity)
{
	// must have used register_entity first to create the object data
	MINTY_ASSERT(m_entityToObjectData.contains(entity), ErrorCode::Argument_KeyNotFound);

	EntityObjectData &entityData = m_entityToObjectData.at(entity);

	// must not be in the simulation, if it is, remove it first please
	MINTY_ASSERT(!entityData.isInSimulation, ErrorCode::Physics_NotInSimulation);

	// delete user pointer data
	delete entityData.data;

	if (entityData.body)
	{
		// delete motion state
		btMotionState *const motionState = entityData.body->getMotionState();
		delete motionState;

		// delete body
		delete entityData.body;
	}

	if (entityData.object)
	{
		// delete collision object
		delete entityData.object;
	}

	// remove from map
	m_entityToObjectData.remove(entity);
}

void Minty::Bullet_PhysicsSimulation::add(Entity const entity)
{
	// must have used register_entity first to create the object data
	MINTY_ASSERT(m_entityToObjectData.contains(entity), ErrorCode::Argument_KeyNotFound);

	// get the object data
	EntityObjectData &entityData = m_entityToObjectData.at(entity);

	// must not already be in the simulation
	MINTY_ASSERT(!entityData.isInSimulation, ErrorCode::Physics_InSimulation);

	Bullet_Object const &objectData = *entityData.data;

	// add to simulation using the proper method based on whether it is a rigidbody or just a collider
	if (entityData.body != nullptr)
	{
		mp_dynamicsWorld->addRigidBody(entityData.body, objectData.layerBit, objectData.layerMask);
	}
	else if (entityData.object != nullptr)
	{
		mp_dynamicsWorld->addCollisionObject(entityData.object, objectData.layerBit, objectData.layerMask);
	}
	else
	{
		// a collider or rigidbody must be registered for this entity in order to add to the simulation
		MINTY_WARNING_F(ErrorCode::Object_NotRegistered, entity);
	}

	entityData.isInSimulation = true;

	// #ifdef MINTY_DEBUG

	// 	SceneManager &sceneManager = SceneManager::get_singleton();
	// 	Ref<Scene> const &scene = sceneManager.get_active();
	// 	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	// 	EntityManager &entityManager = scene->get_entity_manager();
	// 	MINTY_LOG_DEBUG_F("Added static Collider from simulation: {}", entityManager.to_string(objectData->entity));

	// #endif // MINTY_DEBUG
}

void Minty::Bullet_PhysicsSimulation::remove(Entity const entity)
{
	// entity must be registered to be removed
	MINTY_ASSERT(m_entityToObjectData.contains(entity), ErrorCode::Argument_KeyNotFound);

	EntityObjectData &entityData = m_entityToObjectData.at(entity);

	// must be in the simulation to be removed
	MINTY_ASSERT(entityData.isInSimulation, ErrorCode::Physics_NotInSimulation);

	// remove from collision tracking
	remove_collisions_for_object(entityData.data);

	// remove the object from the simulation using the proper method based on whether it's static or dynamic
	if (entityData.body != nullptr)
	{
		mp_dynamicsWorld->removeRigidBody(entityData.body);
	}
	else if (entityData.object != nullptr)
	{
		mp_dynamicsWorld->removeCollisionObject(entityData.object);
	}
	else
	{
		// a collider or rigidbody must be registered for this entity in order to remove from the simulation
		MINTY_WARNING_F(ErrorCode::Object_NotRegistered, entity);
	}

	// mark as not in simulation
	entityData.isInSimulation = false;
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
