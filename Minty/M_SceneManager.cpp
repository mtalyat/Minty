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
		// load new scene
		if (contains(name))
		{
			// unload active scene, if there is one
			if (mp_active && mp_active->unload()) {
				Debug::logError(20, std::format("Failed to unload scene \"{0}\".", mp_active->name()), *mp_active);
			}

			mp_active = mp_scenes->at(name);

			if (mp_active->load()) {
				Debug::logError(21, std::format("Failed to load scene \"{0}\".", mp_active->name()), *mp_active);
			}
		}
		else
		{
			Debug::logError(22, std::format("No scene found for name \"{}\"!", name));
		}
	}

	void SceneManager::reload()
	{
		load(mp_active->name());
	}
}
