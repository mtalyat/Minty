#include "pch.h"
#include "Rigidbody.h"
#include "Minty/Physics/RigidbodyInfo.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_Rigidbody.h"
#endif

using namespace Minty;

Minty::Rigidbody::Rigidbody(RigidbodyInfo const &info)
    : m_collider(info.collider)
{
    MINTY_ASSERT(info.collider != nullptr, ErrorCode::Argument_ExpectedNonNull);
}

Shared<Rigidbody> Minty::Rigidbody::create(RigidbodyInfo const &info)
{
#if defined(MINTY_BULLET)
    return Shared<Bullet_Rigidbody>::create(info);
#else
    return Shared<Rigidbody>();
#endif
}

Shared<Rigidbody> Minty::Rigidbody::create()
{
    RigidbodyInfo info{};
    return create(info);
}
