#include "pch.h"
#include "PhysicsMaterial.h"
#include "Minty/Physics/PhysicsMaterialInfo.h"

using namespace Minty;

Minty::PhysicsMaterial::PhysicsMaterial(PhysicsMaterialInfo const &info)
    : Asset(info.id), m_dynamicFriction(info.dynamicFriction), m_staticFriction(info.staticFriction), m_bounce(info.bounce)
{
}

Shared<PhysicsMaterial> Minty::PhysicsMaterial::create(PhysicsMaterialInfo const &info)
{
    return Shared<PhysicsMaterial>::create(info);
}

Shared<PhysicsMaterial> Minty::PhysicsMaterial::create()
{
    PhysicsMaterialInfo info{};
    return create(info);
}
