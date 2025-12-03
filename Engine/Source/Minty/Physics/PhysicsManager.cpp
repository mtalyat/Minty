#include "pch.h"
#include "PhysicsManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Physics/PhysicsManagerInfo.h"

using namespace Minty;

Minty::PhysicsManager::PhysicsManager(PhysicsManagerInfo const &info)
	: Manager()
{
}

Unique<PhysicsManager> Minty::PhysicsManager::create(PhysicsManagerInfo const &info)
{
	return Unique<PhysicsManager>::create(info);
}

Unique<PhysicsManager> Minty::PhysicsManager::create()
{
	PhysicsManagerInfo info{};
	return create(info);
}

PhysicsManager &Minty::PhysicsManager::get_singleton()
{
	return Application::get_singleton().get_physics_manager();
}
