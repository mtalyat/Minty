#include "pch.h"
#include "PhysicsManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

Owner<PhysicsManager> Minty::PhysicsManager::create(PhysicsManagerBuilder const& builder)
{
	return Owner<PhysicsManager>(builder);
}

PhysicsManager& Minty::PhysicsManager::get_singleton()
{
	Context& context = Context::get_singleton();
	return context.get_physics_manager();
}
