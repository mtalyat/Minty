#include "pch.h"
#include "Bullet_PhysicsSimulation.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_Physics.h"
#include "Platform/Bullet/Bullet_RigidBody.h"

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

void Minty::Bullet_PhysicsSimulation::add_static(Transform const& transform, Collider& collider, Layer const layer)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);

	// create transform data
	btTransform btTransform = Bullet_Physics::to_bullet(transform);

	// create the collision object
	btCollisionObject* collisionObject = new btCollisionObject();
	collisionObject->setCollisionShape(btCollider.get_collision_shape());
	collisionObject->setWorldTransform(btTransform);

	// update collider
	btCollider.set_collision_object(collisionObject);

	// add the collision object to the dynamics world
	mp_dynamicsWorld->addCollisionObject(collisionObject);
}

void Minty::Bullet_PhysicsSimulation::add_dynamic(Transform const& transform, Collider& collider, RigidBody& body, Layer const layer)
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

	// set data
	btBody.set_rigid_body(rigidBody);
	btCollider.set_collision_object(rigidBody);

	// add the rigid body to the dynamics world
	mp_dynamicsWorld->addRigidBody(rigidBody);
}

void Minty::Bullet_PhysicsSimulation::remove_static(Collider& collider)
{
	// remove from dynamics world
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	btCollisionObject* collisionObject = btCollider.get_collision_object();
	MINTY_ASSERT(collisionObject != nullptr, "Collider is not in the PhysicsManager.");
	mp_dynamicsWorld->removeCollisionObject(collisionObject);

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
