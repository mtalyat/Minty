#include "pch.h"
#include "PhysicsSimulation.h"
#if defined(MINTY_BULLET)
#include "Platform/Bullet/Bullet_PhysicsSimulation.h"
#endif

using namespace Minty;

Owner<PhysicsSimulation> Minty::PhysicsSimulation::create(PhysicsSimulationInfo const& info)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_PhysicsSimulation>(info);
#else
    return Owner<PhysicsSimulation>();
#endif
}

Minty::PhysicsSimulation::PhysicsSimulation(PhysicsSimulationInfo const& info)
	: m_gravity(info.gravity)
	, m_physicsManager(info.physicsManager)
	, m_layerManager(info.layerManager)
{
	MINTY_ASSERT(m_physicsManager != nullptr, "PhysicsSimulation requires a PhysicsManager.");
	MINTY_ASSERT(m_layerManager != nullptr, "PhysicsSimulation requires a LayerManager.");
}
