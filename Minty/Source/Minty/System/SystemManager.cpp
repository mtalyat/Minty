#include "pch.h"
#include "SystemManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

System* Minty::SystemManager::add(SystemInfo const* info, Int const priority)
{
	MINTY_ASSERT(info != nullptr, "Given system is not registered.");

	// create the system
	SystemBuilder builder{};
	builder.scene = m_scene;
	builder.info = info;
	System* system = info->create(builder);

	MINTY_ASSERT(!m_systemsByType.contains(info->typeId), F("System already exists: {}", info->name));

	// add the system
	m_systemsByType.add(info->typeId, system);
	auto found = m_systems.find(priority);
	if (found == m_systems.end())
	{
		// create a new list for this priority
		m_systems.add(priority, { system });
	}
	else
	{
		// add to the existing list
		found->get_second().add(system);
	}

	return system;
}

System* Minty::SystemManager::add(SystemInfo const* info)
{
	MINTY_ASSERT(info != nullptr, "Given system is not registered.");
	return add(info, info->defaultPriority);
}

System* Minty::SystemManager::add(TypeID const& typeId)
{
	// get info from type
	return add(Context::get_singleton().get_system_info(typeId));
}

System* Minty::SystemManager::add(String const& name)
{
	return add(Context::get_singleton().get_system_info(name));
}

System* Minty::SystemManager::add(String const& name, Int const priority)
{
	return add(Context::get_singleton().get_system_info(name), priority);
}

void Minty::SystemManager::initialize()
{
	// load all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_load();
		}
	}

	Manager::initialize();
}

void Minty::SystemManager::dispose()
{
	// unload and delete all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_unload();
			delete system;
		}
	}

	// clear data
	m_systems.clear();
	m_systemsByType.clear();

	Manager::dispose();
}

void Minty::SystemManager::update(Time const& time)
{
	// update all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_update(time);
		}
	}
}

void Minty::SystemManager::finalize()
{
	// finalize all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_finalize();
		}
	}
}

void Minty::SystemManager::render()
{
	// render all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_render();
		}
	}
}

void Minty::SystemManager::handle_event(Event& event)
{
	// pass the event on to each of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_event(event);

			if (event.is_processed())
			{
				return;
			}
		}
	}
}

void Minty::SystemManager::serialize(Writer& writer) const
{
	// serialize each system
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			// write the name, only write the priority if it is not the default priority
			if (priority != system->get_info()->defaultPriority)
			{
				writer.write(system->get_info()->name, priority);
			}
			else
			{
				writer.write(system->get_info()->name);
			}

			// write the system data
			writer.indent();
			system->serialize(writer);
			writer.outdent();
		}
	}
}

Bool Minty::SystemManager::deserialize(Reader& reader)
{
	// unload systems
	dispose();

	// deserialize each system
	String name;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		if (!reader.read_name(i, name))
		{
			// failed to read name
			continue;
		}

		// read the priority and create the system
		Int priority;
		System* system;
		if (reader.read(i, priority))
		{
			// use priority since it was given
			system = add(name, priority);
		}
		else
		{
			// use default priority
			system = add(name);
		}

		// enter system
		reader.indent(i);

		// deserialize the system
		if (!system->deserialize(reader))
		{
			MINTY_ERROR(F("Failed to deserialize system: {}", name));
			reader.outdent();
			return false;
			initialize();
		}

		reader.outdent();
	}

	// load the systems
	initialize();

	return true;
}

Owner<SystemManager> Minty::SystemManager::create(Scene* scene, SystemManagerBuilder const& builder)
{
	return Owner<SystemManager>(scene, builder);
}

SystemManager& Minty::SystemManager::get_singleton()
{
	// get active scene
	Ref<Scene> const& activeScene = Context::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, "No active scene. Cannot get SystemManager.");
	return activeScene->get_system_manager();
}
