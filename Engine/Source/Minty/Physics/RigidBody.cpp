#include "pch.h"
#include "RigidBody.h"
#include "Minty/Physics/RigidBodyInfo.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_RigidBody.h"
#endif

using namespace Minty;

Minty::RigidBody::RigidBody(RigidBodyInfo const &info)
    : m_collider(info.collider)
{
    MINTY_ASSERT(info.collider != nullptr, ErrorCode::Argument_ExpectedNonNull);
}

Shared<RigidBody> Minty::RigidBody::create(RigidBodyInfo const &info)
{
#if defined(MINTY_BULLET)
    return Shared<Bullet_RigidBody>::create(info);
#else
    return Shared<RigidBody>();
#endif
}

Shared<RigidBody> Minty::RigidBody::create()
{
    RigidBodyInfo info{};
    return create(info);
}
