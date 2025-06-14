#include "pch.h"
#include "Bullet_PhysicsSimulation.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Platform/Bullet/Bullet_MeshCollider.h"
#include "Platform/Bullet/Bullet_Physics.h"
#include "Platform/Bullet/Bullet_RigidBody.h"
#include "Platform/Bullet/Bullet_ShapeCollider.h"
#include "Platform/Bullet/Bullet_Object.h"

using namespace Minty;

Minty::Bullet_PhysicsSimulation::Bullet_PhysicsSimulation(PhysicsSimulationBuilder const& builder)
	: PhysicsSimulation(builder)
	, mp_broadphase(new btDbvtBroadphase())
	, mp_collisionConfiguration(new btDefaultCollisionConfiguration())
	, mp_dispatcher(new btCollisionDispatcher(mp_collisionConfiguration))
	, mp_solver(new btSequentialImpulseConstraintSolver())
	, mp_dynamicsWorld(new btDiscreteDynamicsWorld(mp_dispatcher, mp_broadphase, mp_solver, mp_collisionConfiguration))
{
	// set gravity
	set_gravity(builder.gravity);
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
	mp_dynamicsWorld->addCollisionObject(collisionObject, layer, layerMask);
}

void Minty::Bullet_PhysicsSimulation::add_dynamic(Entity const entity, Transform const& transform, Collider& collider, RigidBody& body, Layer const layer, Layer const layerMask)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	Bullet_RigidBody& btBody = static_cast<Bullet_RigidBody&>(body);
	btCollisionShape* shape = btCollider.get_collision_shape();

	// create transform data
	btTransform btTransform = Bullet_Physics::to_bullet(transform);

	// set inertia
	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(btBody.get_mass(), inertia);

	// create motion state
	btMotionState* motionState = new btDefaultMotionState(btTransform);

	// create rigid body construction info
	btRigidBody::btRigidBodyConstructionInfo rbInfo(btBody.get_mass(), motionState, shape, inertia);

	// create the rigid body
	btRigidBody* rigidBody = new btRigidBody(rbInfo);

	// create object data
	Bullet_Object* objectData = new Bullet_Object();
	objectData->entity = entity;

	// set the user pointer to the object data
	rigidBody->setUserPointer(objectData);

	// set data
	btBody.set_rigid_body(rigidBody);
	btCollider.set_collision_object(rigidBody);

	// add the rigid body to the dynamics world
	mp_dynamicsWorld->addRigidBody(rigidBody, layer, layerMask);
}

void Minty::Bullet_PhysicsSimulation::remove_static(Collider& collider)
{
	// remove from dynamics world
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	btCollisionObject* collisionObject = btCollider.get_collision_object();
	MINTY_ASSERT(collisionObject != nullptr, "Collider is not in the PhysicsManager.");
	mp_dynamicsWorld->removeCollisionObject(collisionObject);

	// delete user data
	delete collisionObject->getUserPointer();

	// delete the collision object
	delete collisionObject;
	btCollider.set_collision_object(nullptr);
}

void Minty::Bullet_PhysicsSimulation::remove_dynamic(Collider& collider, RigidBody& body)
{
	// remove from dynamics world
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	Bullet_RigidBody& btBody = static_cast<Bullet_RigidBody&>(body);
	btCollisionObject* collisionObject = btCollider.get_collision_object();
	btRigidBody* rigidBody = btBody.get_rigid_body();
	MINTY_ASSERT(collisionObject != nullptr && rigidBody != nullptr, "Collider or RigidBody is not in the PhysicsManager.");
	mp_dynamicsWorld->removeRigidBody(rigidBody);

	// delete user data
	delete collisionObject->getUserPointer();

	// delete the rigid body and motion state
	delete rigidBody->getMotionState();
	delete rigidBody;
	btCollider.set_collision_object(nullptr);
	btBody.set_rigid_body(nullptr);
}

void Minty::Bullet_PhysicsSimulation::set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body)
{
	MINTY_WARNING("TODO: PhysicsManager::set_dynamic()");
}

void Minty::Bullet_PhysicsSimulation::get_dynamic(Transform& transform, Collider const& collider, RigidBody& body)
{
	MINTY_WARNING("TODO: PhysicsManager::get_dynamic()");
}

Bool Minty::Bullet_PhysicsSimulation::raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layerMask, Float const maxDistance) const
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
	rayCallback.m_collisionFilterMask = static_cast<int>(layerMask);

	// perform the raycast
	mp_dynamicsWorld->rayTest(btOrigin, btEnd, rayCallback);

	// check if we hit something
	if (rayCallback.hasHit())
	{
		// get the user data
		Bullet_Object* objectData = static_cast<Bullet_Object*>(rayCallback.m_collisionObject->getUserPointer());
		MINTY_ASSERT(objectData != nullptr, "Raycast hit object does not have user data.");

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
