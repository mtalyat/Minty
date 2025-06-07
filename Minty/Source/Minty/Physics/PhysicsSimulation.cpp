#include "pch.h"
#include "PhysicsSimulation.h"
#if defined(MINTY_BULLET)
#include "Platform/Bullet/Bullet_PhysicsSimulation.h"
#endif

using namespace Minty;

Owner<PhysicsSimulation> Minty::PhysicsSimulation::create(PhysicsSimulationBuilder const& builder)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_PhysicsSimulation>(builder);
#else
    return Owner<PhysicsSimulation>();
#endif
}

Minty::PhysicsSimulation::PhysicsSimulation(PhysicsSimulationBuilder const& builder)
	: m_gravity(builder.gravity)
	, m_physicsManager(builder.physicsManager)
	, m_layerManager(builder.layerManager)
{
	MINTY_ASSERT(m_physicsManager != nullptr, "PhysicsSimulation requires a PhysicsManager.");
	MINTY_ASSERT(m_layerManager != nullptr, "PhysicsSimulation requires a LayerManager.");
}
