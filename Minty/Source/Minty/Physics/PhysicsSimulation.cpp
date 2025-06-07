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
