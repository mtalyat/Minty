#include "pch.h"
#include "M_SystemManager.h"

namespace minty
{
	SystemManager::SystemManager()
		: mp_systems(new std::vector<System*>())
	{}

	SystemManager::~SystemManager()
	{
		// delete each system
		for (auto system : *mp_systems)
		{
			delete system;
		}

		delete mp_systems;
	}

	void SystemManager::emplace(System* const system)
	{
		mp_systems->push_back(system);
	}

	void SystemManager::erase(System* const system)
	{
		for (size_t i = 0; i < mp_systems->size(); i++)
		{
			if (mp_systems->at(i) == system)
			{
				mp_systems->erase(mp_systems->begin() + i);

				return;
			}
		}
	}

	void SystemManager::update()
	{
		for (auto system : *mp_systems)
		{
			system->update();
		}
	}
}
