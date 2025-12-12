#include "pch.h"
#include "Bullet_RigidBody.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Physics/RigidBodyInfo.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_Object.h"
#include "Platform/Bullet/Bullet_Physics.h"

using namespace Minty;

Minty::Bullet_RigidBody::Bullet_RigidBody(RigidBodyInfo const& info)
	: RigidBody(info)
	, mp_body(nullptr)
{
	// get data
	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(*info.collider.get());
	btCollisionShape* const shape = btCollider.get_collision_shape();

	// create transform data
	btTransform btTransform = btTransform::getIdentity();

	// set inertia
	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(info.mass, inertia);

	// create motion state
	btMotionState* motionState = new btDefaultMotionState(btTransform);

	// create rigid body construction info
	btRigidBody::btRigidBodyConstructionInfo rbInfo(info.mass, motionState, shape, inertia);

	// create the rigid body
	btRigidBody* rigidBody = new btRigidBody(rbInfo);

	// create object data
	Bullet_Object* objectData = new Bullet_Object();
	rigidBody->setUserPointer(objectData);

	// set data
	mp_body = rigidBody;
	btCollider.set_collision_object(rigidBody);
}

Minty::Bullet_RigidBody::~Bullet_RigidBody()
{
	delete mp_body->getUserPointer();
	delete mp_body->getMotionState();
	delete mp_body;

	Bullet_Collider& btCollider = static_cast<Bullet_Collider&>(*get_collider().get());
	btCollider.set_collision_object(nullptr);
}

Bool Minty::Bullet_RigidBody::is_static() const
{
	return mp_body->isStaticObject();
}

void Minty::Bullet_RigidBody::set_static(Bool const isStatic)
{
	if (isStatic)
	{
		mp_body->setMassProps(0.0f, btVector3(0, 0, 0));
	}
	else
	{
		Float mass = get_mass();
		btVector3 localInertia(0, 0, 0);
		if (mass != 0.0f)
		{
			mp_body->getCollisionShape()->calculateLocalInertia(static_cast<btScalar>(mass), localInertia);
		}
		mp_body->setMassProps(static_cast<btScalar>(mass), localInertia);
		mp_body->updateInertiaTensor();
	}
}

Bool Minty::Bullet_RigidBody::is_dynamic() const
{
	return !mp_body->isStaticOrKinematicObject();
}

Bool Minty::Bullet_RigidBody::is_kinematic() const
{
    return mp_body->isKinematicObject();
}

void Minty::Bullet_RigidBody::set_kinematic(Bool const isKinematic)
{
	if (isKinematic)
	{
		mp_body->setCollisionFlags(mp_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		mp_body->setActivationState(DISABLE_DEACTIVATION);
	}
	else
	{
		mp_body->setCollisionFlags(mp_body->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
		mp_body->setActivationState(ACTIVE_TAG);
	}
}

Float Minty::Bullet_RigidBody::get_mass() const
{
    btScalar invMass = mp_body->getInvMass();
	if (invMass == 0)
	{
		return 0.0f;
	}
	return static_cast<Float>(1.0f / invMass);
}

void Minty::Bullet_RigidBody::set_mass(Float const mass)
{
	btVector3 localInertia(0, 0, 0);
	if (mass != 0.0f)
	{
		mp_body->getCollisionShape()->calculateLocalInertia(static_cast<btScalar>(mass), localInertia);
	}
	mp_body->setMassProps(static_cast<btScalar>(mass), localInertia);
	mp_body->updateInertiaTensor();
}

Float3 Minty::Bullet_RigidBody::get_position() const
{
    btTransform transform = mp_body->getWorldTransform();
	btVector3 origin = transform.getOrigin();
	return Float3(static_cast<Float>(origin.getX()), static_cast<Float>(origin.getY()), static_cast<Float>(origin.getZ()));
}

void Minty::Bullet_RigidBody::set_position(Float3 const &position)
{
	btTransform transform = mp_body->getWorldTransform();
	transform.setOrigin(btVector3(static_cast<btScalar>(position.x), static_cast<btScalar>(position.y), static_cast<btScalar>(position.z)));
	mp_body->setWorldTransform(transform);
}

Quaternion Minty::Bullet_RigidBody::get_rotation() const
{
	btTransform transform = mp_body->getWorldTransform();
	btQuaternion rotation = transform.getRotation();
	return Quaternion(static_cast<Float>(rotation.getX()), static_cast<Float>(rotation.getY()), static_cast<Float>(rotation.getZ()), static_cast<Float>(rotation.getW()));
}

void Minty::Bullet_RigidBody::set_rotation(Quaternion const& rotation)
{
	btTransform transform = mp_body->getWorldTransform();
	transform.setRotation(btQuaternion(static_cast<btScalar>(rotation.x), static_cast<btScalar>(rotation.y), static_cast<btScalar>(rotation.z), static_cast<btScalar>(rotation.w)));
	mp_body->setWorldTransform(transform);
}

Float3 Minty::Bullet_RigidBody::get_linear_velocity() const
{
	btVector3 velocity = mp_body->getLinearVelocity();
	return Float3(static_cast<Float>(velocity.getX()), static_cast<Float>(velocity.getY()), static_cast<Float>(velocity.getZ()));
}

void Minty::Bullet_RigidBody::set_linear_velocity(Float3 const &velocity)
{
	mp_body->setLinearVelocity(btVector3(static_cast<btScalar>(velocity.x), static_cast<btScalar>(velocity.y), static_cast<btScalar>(velocity.z)));
}

Float Minty::Bullet_RigidBody::get_friction() const
{
	return static_cast<Float>(mp_body->getFriction());
}

void Minty::Bullet_RigidBody::set_friction(Float const friction)
{
	mp_body->setFriction(static_cast<btScalar>(friction));
}

Float Minty::Bullet_RigidBody::get_bounce() const
{
	return static_cast<Float>(mp_body->getRestitution());
}

void Minty::Bullet_RigidBody::set_bounce(Float const bounce)
{
	mp_body->setRestitution(static_cast<btScalar>(bounce));
}

void Minty::Bullet_RigidBody::set_entity(Entity const entity)
{
	Bullet_Object* objectData = static_cast<Bullet_Object*>(mp_body->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::Argument_KeyNotFound);
	objectData->entity = entity;
}

Entity Minty::Bullet_RigidBody::get_entity() const
{
	Bullet_Object* objectData = static_cast<Bullet_Object*>(mp_body->getUserPointer());
	MINTY_ASSERT(objectData != nullptr, ErrorCode::Argument_KeyNotFound);
	return objectData->entity;
}

void Minty::Bullet_RigidBody::add_force(Float3 const &force, Force const mode)
{
	switch(mode)
	{
	case Force::Continuous:
		mp_body->applyCentralForce(btVector3(static_cast<btScalar>(force.x), static_cast<btScalar>(force.y), static_cast<btScalar>(force.z)));
		break;
	case Force::Impulse:
		mp_body->applyCentralImpulse(btVector3(static_cast<btScalar>(force.x), static_cast<btScalar>(force.y), static_cast<btScalar>(force.z)));
		break;
	default:
		MINTY_NOT_IMPLEMENTED();
		break;
	};
}
