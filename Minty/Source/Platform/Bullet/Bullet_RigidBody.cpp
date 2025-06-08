#include "pch.h"
#include "Bullet_RigidBody.h"

using namespace Minty;

Minty::Bullet_RigidBody::Bullet_RigidBody(RigidBodyBuilder const& builder)
	: RigidBody(builder)
	, mp_body(nullptr)
{
	
}
