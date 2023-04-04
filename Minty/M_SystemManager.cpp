#include "pch.h"
#include "M_SystemManager.h"

namespace minty
{
	SystemManager::SystemManager()
		: mp_systems(new std::map<int, std::set<System*>>())
	{}

	SystemManager::~SystemManager()
	{
		// delete each system
		for (auto& pair : *mp_systems)
		{
			for (auto system : pair.second)
			{
				delete system;
			}
		}

		delete mp_systems;
	}

	void SystemManager::emplace(System* const system, int const priority)
	{
		auto found = mp_systems->find(priority);

		if (found == mp_systems->end())
		{
			// new list
			mp_systems->emplace(priority, std::set<System*>());
			mp_systems->at(priority).emplace(system);
		}
		else
		{
			// existing list
			found->second.emplace(system);
		}
	}

	void SystemManager::erase(System* const system)
	{
		// find system, remove it from list
		for (auto& pair : *mp_systems)
		{
			if (pair.second.erase(system))
			{
				// found
				return;
			}
		}
	}

	void SystemManager::load()
	{
		for (auto& pair : *mp_systems)
		{
			for (auto system : pair.second)
			{
				system->load();
			}
		}
	}

	void SystemManager::update()
	{
		for (auto& pair : *mp_systems)
		{
			for (auto system : pair.second)
			{
				if (system->isEnabled())
				{
					system->update();
				}
			}
		}
	}

	void SystemManager::fixedUpdate()
	{
		for (auto& pair : *mp_systems)
		{
			for (auto system : pair.second)
			{
				if (system->isEnabled())
				{
					system->fixedUpdate();
				}
			}
		}
	}
	
	void SystemManager::unload()
	{
		for (auto& pair : *mp_systems)
		{
			for (auto system : pair.second)
			{
				system->unload();
			}
		}
	}
}
