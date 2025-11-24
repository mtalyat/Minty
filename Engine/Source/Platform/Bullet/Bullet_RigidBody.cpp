#include "pch.h"
#include "Bullet_RigidBody.h"

using namespace Minty;

Minty::Bullet_RigidBody::Bullet_RigidBody(RigidBodyInfo const& info)
	: RigidBody(info)
	, mp_body(nullptr)
{
	
}
