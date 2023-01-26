#include "pch.h"

#include "M_SceneManager.h"
#include "M_Scene.h"
#include "M_Debug.h"

namespace minty
{
	SceneManager::~SceneManager()
	{
		for (auto pair : *mp_scenes)
		{
			delete pair.second;
		}

		delete mp_scenes;
	}

	bool SceneManager::contains(std::string const& name)
	{
		return mp_scenes->find(name) != mp_scenes->end();
	}

	bool SceneManager::add(Scene* const scene)
	{
		std::string const& name = scene->name();

		if (!contains(name))
		{
			mp_scenes->emplace(name, scene);
			return true;
		}

		return false;
	}

	void SceneManager::load(std::string const& name)
	{
		// stop current scene
		if (mp_active)
		{
			if (mp_active->onUnload()) {
				Debug::logError(std::format("Failed to stop scene \"{0}\".", name), *mp_active);
			}

			mp_active = nullptr;
		}

		// load new scene
		if (contains(name))
		{
			mp_active = mp_scenes->at(name);

			if (mp_active->onLoad()) {
				Debug::logError(std::format("Failed to start scene \"{0}\".", name), *mp_active);
			}
		}
		else
		{
			// scene name not found
			Debug::logError(std::format("No scene found for name \"{0}\".", name));
		}
	}
}
