#include "pch.h"
#include "SystemManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

void Minty::SystemManager::add(TypeID const& typeId, System* system)
{
	MINTY_ASSERT(!m_systemsByType.contains(typeId), F("System already exists with the TypeID: {}", typeId));

	// add the system
	m_systemsByType.add(typeId, m_systems.get_size());
	m_systems.add(system);
}

void Minty::SystemManager::add(String const& name)
{
	// look up creation from Context
	Context& context = Context::get_singleton();

	SystemInfo const* info = context.get_system_info(name);
	MINTY_ASSERT(info != nullptr, F("System is not registered with the name: {}", name));

	// create system
	SystemBuilder builder{};
	builder.scene = m_scene;
	System* system = info->create(builder);
	
	add(info->typeId, system);
}

void Minty::SystemManager::initialize()
{
	// load all of the systems
	for (System* system : m_systems)
	{
		system->on_load();
	}

	Manager::initialize();
}

void Minty::SystemManager::dispose()
{
	// unload and delete all of the systems
	for (System* system : m_systems)
	{
		system->on_unload();
		delete system;
	}

	// clear data
	m_systems.clear();
	m_systemsByType.clear();

	Manager::dispose();
}

void Minty::SystemManager::update(Time const& time)
{
	// update all of the systems
	for (System* system : m_systems)
	{
		system->on_update(time);
	}
}

void Minty::SystemManager::finalize()
{
	// finalize all of the systems
	for (System* system : m_systems)
	{
		system->on_finalize();
	}
}

void Minty::SystemManager::render()
{
	// render all of the systems
	for (System* system : m_systems)
	{
		system->on_render();
	}
}

Owner<SystemManager> Minty::SystemManager::create(SystemManagerBuilder const& builder)
{
	return Owner<SystemManager>(builder);
}

SystemManager& Minty::SystemManager::get_singleton()
{
	// get active scene
	Ref<Scene> const& activeScene = Context::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, "No active scene. Cannot get SystemManager.");
	return activeScene->get_system_manager();
}
