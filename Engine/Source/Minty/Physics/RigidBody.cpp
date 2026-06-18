#include "pch.h"
#include "Rigidbody.h"
#include "Minty/Physics/RigidbodyInfo.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_Rigidbody.h"
#endif

using namespace Minty;

Minty::Rigidbody::Rigidbody(RigidbodyInfo const &info)
    : m_rotationConstraints(info.rotationConstraints), m_mass(info.mass), m_linearDamping(info.linearDamping), m_angularDamping(info.angularDamping), m_isKinematic(info.isKinematic), m_isStatic(info.isStatic)
{
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

void Minty::Rigidbody::set_mass(Float const mass)
{
    // mass cannot be negative
    MINTY_ASSERT(mass >= 0.0f, ErrorCode::Argument_ExpectedAboveZero);
    m_mass = mass;
}
