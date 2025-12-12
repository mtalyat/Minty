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

using namespace Minty;

Minty::Bullet_PhysicsSimulation::Bullet_PhysicsSimulation(PhysicsSimulationInfo const& info)
	: PhysicsSimulation(info)
	, mp_broadphase(new btDbvtBroadphase())
	, mp_collisionConfiguration(new btDefaultCollisionConfiguration())
	, mp_dispatcher(new btCollisionDispatcher(mp_collisionConfiguration))
	, mp_solver(new btSequentialImpulseConstraintSolver())
	, mp_dynamicsWorld(new btDiscreteDynamicsWorld(mp_dispatcher, mp_broadphase, mp_solver, mp_collisionConfiguration))
{
	// set gravity
	set_gravity(info.gravity);
}

Size Minty::Bullet_PhysicsSimulation::get_size() const
{
	return static_cast<Size>(mp_dynamicsWorld->getNumCollisionObjects());
}

void Minty::Bullet_PhysicsSimulation::set_gravity(Float3 const& gravity)
{
	// set the gravity in the dynamics world
	mp_dynamicsWorld->setGravity(Bullet_Physics::to_bullet(gravity));
	
	PhysicsSimulation::set_gravity(gravity);
}

void Minty::Bullet_PhysicsSimulation::step(Float const elapsedTime)
{
	mp_dynamicsWorld->stepSimulation(elapsedTime, 1, DEFAULT_PHYSICS_TIME_STEP);
}

void Minty::Bullet_PhysicsSimulation::add_static(Entity const entity, Transform const& transform, Collider& collider, Layer const layer, Layer const layerMask)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);

	// create transform data
	btTransform btTransform = Bullet_Physics::to_bullet(transform);

	// create the collision object
	btCollisionObject* collisionObject = new btCollisionObject();
	collisionObject->setCollisionShape(btCollider.get_collision_shape());
	collisionObject->setWorldTransform(btTransform);

	// create object data
	Bullet_Object* objectData = new Bullet_Object();
	objectData->entity = entity;

	// set the user pointer to the object data
	collisionObject->setUserPointer(objectData);

	// update collider
	btCollider.set_collision_object(collisionObject);

	// add the collision object to the dynamics world
	mp_dynamicsWorld->addCollisionObject(collisionObject, LayerManager::layer_to_bit(layer), layerMask);
}

void Minty::Bullet_PhysicsSimulation::add_dynamic(Entity const entity, RigidBody& body, Layer const layer, Layer const layerMask)
{
	// get data
	btRigidBody* const rigidBody = static_cast<btRigidBody*>(body.get_native());

	// add the rigid body to the dynamics world
	mp_dynamicsWorld->addRigidBody(rigidBody, LayerManager::layer_to_bit(layer), layerMask);
}

void Minty::Bullet_PhysicsSimulation::remove_static(Collider& collider)
{
	// remove from dynamics world
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	btCollisionObject* collisionObject = btCollider.get_collision_object();
	MINTY_ASSERT(collisionObject != nullptr, ErrorCode::Argument_KeyNotFound);
	mp_dynamicsWorld->removeCollisionObject(collisionObject);

	// delete user data
	delete collisionObject->getUserPointer();

	// delete the collision object
	delete collisionObject;
	btCollider.set_collision_object(nullptr);
}

void Minty::Bullet_PhysicsSimulation::remove_dynamic(RigidBody& body)
{
	// get data
	btRigidBody* const rigidBody = static_cast<btRigidBody*>(body.get_native());

	// remove from dynamics world
	mp_dynamicsWorld->removeRigidBody(rigidBody);
}

Bool Minty::Bullet_PhysicsSimulation::raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layer, Layer const layerMask, Float const maxDistance) const
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
		Bullet_Object* objectData = static_cast<Bullet_Object*>(rayCallback.m_collisionObject->getUserPointer());
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
		btCollisionObject* obj = mp_dynamicsWorld->getCollisionObjectArray()[i];
		mp_dynamicsWorld->removeCollisionObject(obj);
	}
}
