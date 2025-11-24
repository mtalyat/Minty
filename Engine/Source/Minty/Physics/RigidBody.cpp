#include "pch.h"
#include "RigidBody.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_RigidBody.h"
#endif

using namespace Minty;

Owner<RigidBody> Minty::RigidBody::create(RigidBodyInfo const& info)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_RigidBody>(info);
#else
    return Owner<RigidBody>();
#endif
}
