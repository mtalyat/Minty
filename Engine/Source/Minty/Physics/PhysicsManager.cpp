#include "pch.h"
#include "PhysicsManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

Owner<PhysicsManager> Minty::PhysicsManager::create(PhysicsManagerInfo const& info)
{
	return Owner<PhysicsManager>(info);
}

PhysicsManager& Minty::PhysicsManager::get_singleton()
{
	Context& context = Context::get_singleton();
	return context.get_physics_manager();
}
