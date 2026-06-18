#include "pch.h"
#include "Bullet_Rigidbody.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Physics/RigidbodyInfo.h"
#include "Platform/Bullet/Bullet_Collider.h"
#include "Platform/Bullet/Bullet_Object.h"
#include "Platform/Bullet/Bullet_Physics.h"

using namespace Minty;

Minty::Bullet_Rigidbody::Bullet_Rigidbody(RigidbodyInfo const& info)
	: Rigidbody(info), mp_body(nullptr)
{
}

Minty::Bullet_Rigidbody::~Bullet_Rigidbody()
{
	// mp_body not owned by the rigid body
}

void Minty::Bullet_Rigidbody::bind_rigidbody(btRigidBody * const body)
{
	// set the body and update values to match the rigid body properties
	mp_body = body;

	if (body)
	{
		set_static(*body, is_static());
		set_kinematic(*body, is_kinematic());
		set_mass(*body, get_mass());
		set_rotation_constraints(*body, get_rotation_constraints());
		set_damping(*body, get_linear_damping(), get_angular_damping());
	}
}

void Minty::Bullet_Rigidbody::set_static(Bool const isStatic)
{
	Rigidbody::set_static(isStatic);

	if(mp_body)
	{
		set_static(*mp_body, isStatic);
	}
}

void Minty::Bullet_Rigidbody::set_kinematic(Bool const isKinematic)
{
	Rigidbody::set_kinematic(isKinematic);

	if (mp_body)
	{
		set_kinematic(*mp_body, isKinematic);
	}
}

void Minty::Bullet_Rigidbody::set_mass(Float const mass)
{
	Rigidbody::set_mass(mass);

	if (mp_body)
	{
		set_mass(*mp_body, mass);
	}
}

void Minty::Bullet_Rigidbody::set_linear_damping(Float const linearDamping)
{
	Rigidbody::set_linear_damping(linearDamping);

	if (mp_body)
	{
		mp_body->setDamping(static_cast<btScalar>(linearDamping), mp_body->getAngularDamping());
	}
}

void Minty::Bullet_Rigidbody::set_angular_damping(Float const angularDamping)
{
	Rigidbody::set_angular_damping(angularDamping);

	if (mp_body)
	{
		mp_body->setDamping(mp_body->getLinearDamping(), static_cast<btScalar>(angularDamping));
	}
}

void Minty::Bullet_Rigidbody::set_rotation_constraints(Constraints const constraints)
{
	Rigidbody::set_rotation_constraints(constraints);

	if (mp_body)
	{
		set_rotation_constraints(*mp_body, constraints);
	}
}

Float3 Minty::Bullet_Rigidbody::get_simulation_position() const
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);

    btTransform transform = mp_body->getWorldTransform();
	btVector3 origin = transform.getOrigin();
	return Float3(static_cast<Float>(origin.getX()), static_cast<Float>(origin.getY()), static_cast<Float>(origin.getZ()));
}

void Minty::Bullet_Rigidbody::set_simulation_position(Float3 const &position)
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);

	btTransform transform = mp_body->getWorldTransform();
	transform.setOrigin(btVector3(static_cast<btScalar>(position.x), static_cast<btScalar>(position.y), static_cast<btScalar>(position.z)));
	mp_body->setWorldTransform(transform);

	if(btMotionState* const motionState = mp_body->getMotionState())
	{
		motionState->setWorldTransform(transform);
	}

	mp_body->activate();
}

Quaternion Minty::Bullet_Rigidbody::get_simulation_rotation() const
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	btTransform transform = mp_body->getWorldTransform();
	btQuaternion rotation = transform.getRotation();
	return Bullet_Physics::to_minty(rotation);
}

void Minty::Bullet_Rigidbody::set_simulation_rotation(Quaternion const& rotation)
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	btTransform transform = mp_body->getWorldTransform();
	transform.setRotation(btQuaternion(static_cast<btScalar>(rotation.x), static_cast<btScalar>(rotation.y), static_cast<btScalar>(rotation.z), static_cast<btScalar>(rotation.w)));
	mp_body->setWorldTransform(transform);

	if (btMotionState* const motionState = mp_body->getMotionState())
	{
		motionState->setWorldTransform(transform);
	}
	
	mp_body->activate();
}

Float3 Minty::Bullet_Rigidbody::get_simulation_linear_velocity() const
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	btVector3 velocity = mp_body->getLinearVelocity();
	return Float3(static_cast<Float>(velocity.getX()), static_cast<Float>(velocity.getY()), static_cast<Float>(velocity.getZ()));
}

void Minty::Bullet_Rigidbody::set_simulation_linear_velocity(Float3 const &velocity)
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	mp_body->setLinearVelocity(btVector3(static_cast<btScalar>(velocity.x), static_cast<btScalar>(velocity.y), static_cast<btScalar>(velocity.z)));
}

Float3 Minty::Bullet_Rigidbody::get_simulation_angular_velocity() const
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	btVector3 const angularVelocity = mp_body->getAngularVelocity();
	return Bullet_Physics::to_minty(angularVelocity);
}

void Minty::Bullet_Rigidbody::set_simulation_angular_velocity(Float3 const &velocity)
{
	MINTY_ASSERT(mp_body != nullptr, ErrorCode::Object_NotRegistered);
	
	btVector3 const angularVelocity = Bullet_Physics::to_bullet(velocity);
	mp_body->setAngularVelocity(angularVelocity);
}

void Minty::Bullet_Rigidbody::add_force(Float3 const &force, Force const mode)
{
	switch(mode)
	{
	case Force::Continuous:
		mp_body->applyCentralForce(btVector3(static_cast<btScalar>(force.x * m_mass), static_cast<btScalar>(force.y * m_mass), static_cast<btScalar>(force.z * m_mass)));
		break;
	case Force::Impulse:
		mp_body->applyCentralImpulse(btVector3(static_cast<btScalar>(force.x * m_mass), static_cast<btScalar>(force.y * m_mass), static_cast<btScalar>(force.z * m_mass)));
		break;
	default:
		MINTY_NOT_IMPLEMENTED();
		break;
	};
}

void Minty::Bullet_Rigidbody::set_static(btRigidBody& body, Bool const isStatic)
{
	if (isStatic)
	{
		body.setCollisionFlags(body.getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	}
	else
	{
		body.setCollisionFlags(body.getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
	}
}

void Minty::Bullet_Rigidbody::set_kinematic(btRigidBody& body, Bool const isKinematic)
{
	if (isKinematic)
	{
		body.setCollisionFlags(body.getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		body.setActivationState(DISABLE_DEACTIVATION);
	}
	else
	{
		body.setCollisionFlags(body.getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
		body.setActivationState(ACTIVE_TAG);
	}
}

void Minty::Bullet_Rigidbody::set_mass(btRigidBody& body, Float const mass)
{
	btVector3 localInertia(0, 0, 0);
	if (mass >= 0.0f)
	{
		body.getCollisionShape()->calculateLocalInertia(static_cast<btScalar>(mass), localInertia);
	}
	body.setMassProps(static_cast<btScalar>(mass), localInertia);
	body.updateInertiaTensor();
}

void Minty::Bullet_Rigidbody::set_rotation_constraints(btRigidBody& body, Constraints const constraints)
{
	btVector3 angularFactor(1, 1, 1);
	if ((constraints & Constraints::X) == Constraints::X)
	{
		angularFactor.setX(0);
	}
	if ((constraints & Constraints::Y) == Constraints::Y)
	{
		angularFactor.setY(0);
	}
	if ((constraints & Constraints::Z) == Constraints::Z)
	{
		angularFactor.setZ(0);
	}
	body.setAngularFactor(angularFactor);
}

void Minty::Bullet_Rigidbody::set_damping(btRigidBody & body, Float const linearDamping, Float const angularDamping)
{
	body.setDamping(static_cast<btScalar>(linearDamping), static_cast<btScalar>(angularDamping));
}
