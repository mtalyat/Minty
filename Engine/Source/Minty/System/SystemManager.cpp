#include "pch.h"
#include "SystemManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Debug/Trace.h"

using namespace Minty;

System* Minty::SystemManager::add(SystemData const* data, Int const priority)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::System_NotRegistered);

	// create the system
	SystemInfo info{};
	info.priority = priority;
	info.scene = m_scene;
	info.info = data;
	System* system = data->create(info);

	MINTY_ASSERT(!m_systemsByType.contains(data->typeId), ErrorCode::Argument_KeyAlreadyExists, data->name);

	// add the system
	m_systemsByType.add(data->typeId, system);
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

System* Minty::SystemManager::add(SystemData const* data)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::System_NotRegistered);
	return add(data, data->defaultPriority);
}

System* Minty::SystemManager::add(TypeID const& typeId)
{
	// get info from type
	return add(Application::get_singleton().get_system_info(typeId));
}

System* Minty::SystemManager::add(String const& name)
{
	return add(Application::get_singleton().get_system_info(name));
}

System* Minty::SystemManager::add(String const& name, Int const priority)
{
	return add(Application::get_singleton().get_system_info(name), priority);
}

System* Minty::SystemManager::get_system(String const& name) const
{
	// get the system info
	SystemData const& data = Application::get_singleton().get_system_info(name);

	// get the system by type
	auto it = m_systemsByType.find(data.typeId);
	// check if it exists
	if (it == m_systemsByType.end())
	{
		// does not exist
		return nullptr;
	}

	// return the system
	return it->get_second();
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

void Minty::SystemManager::frame_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	// update all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_frame_update(time);
		}
	}
}

void Minty::SystemManager::fixed_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	// fixed update all of the systems
	for (auto const& [priority, list] : m_systems)
	{
		for (System* system : list)
		{
			system->on_fixed_update(time);
		}
	}
}

void Minty::SystemManager::finalize()
{
	MINTY_TRACE_SCOPE();

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
	MINTY_TRACE_SCOPE();

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
	MINTY_TRACE_SCOPE();

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
			if (priority != system->get_data()->defaultPriority)
			{
				writer.write(system->get_data()->name, priority);
			}
			else
			{
				writer.write(system->get_data()->name);
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
	// deserialize each system
	String name;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		if (!reader.read_name(i, name))
		{
			// failed to read name
			continue;
		}

		// get the system if it already exists
		System* system = get_system(name);

		Int priority;
		if (system)
		{
			// move the system if it has a new priority
			if (reader.read(i, priority) && priority != system->get_priority())
			{
				m_systems.at(system->get_priority()).remove(system);
				system->m_priority = priority;
				auto it = m_systems.find(priority);
				if (it == m_systems.end())
				{
					// create a new list for this priority
					m_systems.add(priority, { system });
				}
				else
				{
					// add to the existing list
					m_systems.at(priority).add(system);
				}
			}
		}
		else
		{
			// read the priority and create a new system
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
		}

		// enter system
		reader.indent(i);

		// deserialize the system
		if (!system->deserialize(reader))
		{
			MINTY_ABORT(ErrorCode::Serialization_Failed, name);
		}

		reader.outdent();
	}

	return true;
}

Shared<SystemManager> Minty::SystemManager::create(Scene* scene, SystemManagerInfo const& info)
{
	return Shared<SystemManager>(scene, info);
}

SystemManager& Minty::SystemManager::get_singleton()
{
	// get active scene
	Ref<Scene> const& activeScene = Application::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, ErrorCode::Scene_NoActiveScene);
	return activeScene->get_system_manager();
}
