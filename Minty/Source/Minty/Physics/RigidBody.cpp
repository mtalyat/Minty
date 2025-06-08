#include "pch.h"
#include "RigidBody.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_RigidBody.h"
#endif

using namespace Minty;

Owner<RigidBody> Minty::RigidBody::create(RigidBodyBuilder const& builder)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_RigidBody>(builder);
#else
    return Owner<RigidBody>();
#endif
}
