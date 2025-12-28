#include "pch.h"
#include "SystemManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Debug/Trace.h"
#include "Minty/System/SystemManagerInfo.h"
#include "Minty/System/SystemInfo.h"
#include "Minty/System/System.h"
#include "Minty/System/SystemData.h"
#include "Minty/Event/Event.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Scene/SceneManager.h"
#include "Minty/Scene/Scene.h"

using namespace Minty;

Lookup<TypeID, SystemData> Minty::SystemManager::s_registeredSystems;

Minty::SystemManager::SystemManager(Ref<Scene> const& scene, SystemManagerInfo const &info)
	: SubManager(scene), m_systems(), m_systemsByType()
{
	// load all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_load();
		}
	}
}

Minty::SystemManager::~SystemManager()
{
	// unload and delete all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_unload();
			delete system;
		}
	}
}

System *Minty::SystemManager::add(SystemData const &data, Int const priority)
{
	// create the system
	SystemInfo info{};
	info.priority = priority;
	info.scene = get_scene_ref();
	info.info = &data;
	System *system = data.create(info);

	MINTY_ASSERT_F(!m_systemsByType.contains(data.typeId), ErrorCode::Argument_KeyAlreadyExists, data.name);

	// add the system
	m_systemsByType.add(data.typeId, system);
	auto found = m_systems.find(priority);
	if (found == m_systems.end())
	{
		// create a new list for this priority
		m_systems.add(priority, {system});
	}
	else
	{
		// add to the existing list
		found->get_second().add(system);
	}

	// if the scene is loaded, load the system
	if (get_scene().is_loaded())
	{
		system->on_load();
	}

	return system;
}

System *Minty::SystemManager::add(SystemData const &data)
{
	return add(data, data.defaultPriority);
}

System *Minty::SystemManager::add(TypeID const &typeId)
{
	// get info from type
	return add(get_system_info(typeId));
}

System *Minty::SystemManager::add(String const &name)
{
	return add(get_system_info(name));
}

System *Minty::SystemManager::add(String const &name, Int const priority)
{
	return add(get_system_info(name), priority);
}

System *Minty::SystemManager::get_system(String const &name) const
{
	// get the system info
	SystemData const &data = get_system_info(name);

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

void Minty::SystemManager::on_scene_load()
{
	MINTY_TRACE_SCOPE();

	// load all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_load();
		}
	}
}

void Minty::SystemManager::on_scene_unload()
{
	MINTY_TRACE_SCOPE();

	// unload all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_unload();
		}
	}
}

void Minty::SystemManager::frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// update all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_frame_update(time);
		}
	}
}

void Minty::SystemManager::fixed_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// fixed update all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_fixed_update(time);
		}
	}
}

void Minty::SystemManager::finalize()
{
	MINTY_TRACE_SCOPE();

	// finalize all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_finalize();
		}
	}
}

void Minty::SystemManager::render()
{
	MINTY_TRACE_SCOPE();

	// render all of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_render();
		}
	}
}

void Minty::SystemManager::handle_event(Event &event)
{
	MINTY_TRACE_SCOPE();

	// pass the event on to each of the systems
	for (auto const &[priority, list] : m_systems)
	{
		for (System *system : list)
		{
			system->on_event(event);

			if (event.is_processed())
			{
				return;
			}
		}
	}
}

Shared<SystemManager> Minty::SystemManager::create(Ref<Scene> const& scene, SystemManagerInfo const &info)
{
	return Shared<SystemManager>::create(scene, info);
}

Shared<SystemManager> Minty::SystemManager::create(Ref<Scene> const& scene)
{
	SystemManagerInfo info{};
	return create(scene, info);
}

SystemManager &Minty::SystemManager::get_singleton()
{
	// get from the active scene
	Ref<Scene> const &activeScene = SceneManager::get_singleton().get_active();
	MINTY_ASSERT(activeScene != nullptr, ErrorCode::Scene_NoActiveScene);
	return activeScene->get_system_manager();
}

void Minty::Serializer<SystemManager>::serialize(Writer &writer, SystemManager const &value)
{
	// serialize each system
	for (auto const &[priority, list] : value.m_systems)
	{
		for (System *system : list)
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

void Minty::Serializer<SystemManager>::deserialize(Reader &reader, SystemManager &value)
{
	// deserialize each system and its priority
	String name;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		if (!reader.read_name(i, name))
		{
			// failed to read name
			continue;
		}

		// get the system if it already exists
		System *system = get_system(name);

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
					value.m_systems.add(priority, {system});
				}
				else
				{
					// add to the existing list
					value.m_systems.at(priority).add(system);
				}
			}
		}
		else
		{
			// read the priority and create a new system
			if (reader.read(i, priority))
			{
				// use priority since it was given
				system = value.add(name, priority);
			}
			else
			{
				// use default priority
				system = value.add(name);
			}
		}
	}
}