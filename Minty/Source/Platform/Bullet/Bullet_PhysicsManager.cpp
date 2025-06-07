#include "pch.h"
#include "Bullet_PhysicsManager.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_RigidBody.h"

using namespace Minty;

Minty::Bullet_PhysicsManager::Bullet_PhysicsManager(Scene* scene, PhysicsManagerBuilder const& builder)
	: PhysicsManager(scene, builder)
	, mp_broadphase(new btDbvtBroadphase())
	, mp_collisionConfiguration(new btDefaultCollisionConfiguration())
	, mp_dispatcher(new btCollisionDispatcher(mp_collisionConfiguration))
	, mp_solver(new btSequentialImpulseConstraintSolver())
	, mp_dynamicsWorld(new btDiscreteDynamicsWorld(mp_dispatcher, mp_broadphase, mp_solver, mp_collisionConfiguration))
{
	// set gravity
	mp_dynamicsWorld->setGravity(to_bullet(builder.gravity));
}

Minty::Bullet_PhysicsManager::~Bullet_PhysicsManager()
{
	delete mp_dynamicsWorld;
	delete mp_solver;
	delete mp_dispatcher;
	delete mp_collisionConfiguration;
	delete mp_broadphase;
}

void Minty::Bullet_PhysicsManager::step(Float const elapsedTime)
{
	mp_dynamicsWorld->stepSimulation(elapsedTime, 1, DEFAULT_PHYSICS_TIME_STEP);
}

void Minty::Bullet_PhysicsManager::initialize()
{
	PhysicsManager::initialize();
}

void Minty::Bullet_PhysicsManager::dispose()
{
	// clear the dynamics world
	Int count = mp_dynamicsWorld->getNumCollisionObjects();
	for (Int i = count - 1; i >= 0; i--)
	{
		// deleting handled by the individual objects
		btCollisionObject* obj = mp_dynamicsWorld->getCollisionObjectArray()[i];
		mp_dynamicsWorld->removeCollisionObject(obj);
	}

	PhysicsManager::dispose();
}

void Minty::Bullet_PhysicsManager::add_static(Transform const& transform, Collider& collider)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);

	// create transform data
	btTransform btTransform = to_bullet(transform);

	// create the collision object
	btCollisionObject* collisionObject = new btCollisionObject();
	collisionObject->setCollisionShape(btCollider.get_collision_shape());
	collisionObject->setWorldTransform(btTransform);

	// update collider
	btCollider.set_collision_object(collisionObject);

	// add the collision object to the dynamics world
	mp_dynamicsWorld->addCollisionObject(collisionObject);
}

void Minty::Bullet_PhysicsManager::add_dynamic(Transform const& transform, Collider& collider, RigidBody& body)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(collider);
	Bullet_RigidBody& btBody = static_cast<Bullet_RigidBody&>(body);
	btCollisionShape* shape = btCollider.get_collision_shape();

	// create transform data
	btTransform btTransform = to_bullet(transform);

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

void Minty::Bullet_PhysicsManager::remove_static(Collider& collider)
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

void Minty::Bullet_PhysicsManager::remove_dynamic(Collider& collider, RigidBody& body)
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

void Minty::Bullet_PhysicsManager::set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body)
{
	MINTY_WARNING("TODO: PhysicsManager::set_dynamic()");
}

void Minty::Bullet_PhysicsManager::get_dynamic(Transform& transform, Collider const& collider, RigidBody& body)
{
	MINTY_WARNING("TODO: PhysicsManager::get_dynamic()");
}
