#include "pch.h"
#include "PhysicsSimulation.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Physics/PhysicsSimulationInfo.h"
#if defined(MINTY_BULLET)
#include "Platform/Bullet/Bullet_PhysicsSimulation.h"
#endif

using namespace Minty;

Shared<PhysicsSimulation> Minty::PhysicsSimulation::create(PhysicsSimulationInfo const& info)
{
#if defined(MINTY_BULLET)
	return Shared<Bullet_PhysicsSimulation>::create(info);
#else
    return Shared<PhysicsSimulation>();
#endif
}

Shared<PhysicsSimulation> Minty::PhysicsSimulation::create()
{
	PhysicsSimulationInfo info{};
	return create(info);
}

Minty::PhysicsSimulation::PhysicsSimulation(PhysicsSimulationInfo const& info)
	: m_gravity(info.gravity)
{
}
