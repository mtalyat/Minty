#include "pch.h"
#include "PhysicsSimulation.h"
#include "Minty/Debug/Assert.h"
#if defined(MINTY_BULLET)
#include "Platform/Bullet/Bullet_PhysicsSimulation.h"
#endif

using namespace Minty;

Shared<PhysicsSimulation> Minty::PhysicsSimulation::create(PhysicsSimulationInfo const& info)
{
#if defined(MINTY_BULLET)
	return Shared<Bullet_PhysicsSimulation>(info);
#else
    return Shared<PhysicsSimulation>();
#endif
}

Minty::PhysicsSimulation::PhysicsSimulation(PhysicsSimulationInfo const& info)
	: m_gravity(info.gravity)
	, m_physicsManager(info.physicsManager)
	, m_layerManager(info.layerManager)
{
	MINTY_ASSERT(m_physicsManager != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(m_layerManager != nullptr, ErrorCode::Argument_ExpectedNonNull);
}
