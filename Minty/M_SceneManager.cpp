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

	void SceneManager::load(std::string const& name, bool const unloadActive)
	{
		// load new scene
		if (contains(name))
		{
			// stop current scene, if supposed to
			if (unloadActive)
			{
				unload();
			}

			push(mp_scenes->at(name));

			if (mp_active->load()) {
				Debug::logError(21, std::format("Failed to load scene \"{0}\".", mp_active->name()), *mp_active);
			}
		}
		else
		{
			Debug::logError(22, std::format("No scene found for name \"{}\"!", name));
		}
	}

	void SceneManager::unload()
	{
		if (mp_active)
		{
			if (mp_active->unload()) {
				Debug::logError(20, std::format("Failed to unload scene \"{0}\".", mp_active->name()), *mp_active);
			}

			pop();
		}
	}

	void SceneManager::reload()
	{
		load(mp_active->name());
	}
	
	void SceneManager::push(Scene* const scene)
	{
		mp_activeScenes->push_back(scene);
		mp_active = scene;
	}
	
	void SceneManager::pop()
	{
		mp_activeScenes->pop_back();

		if (mp_activeScenes->empty())
		{
			mp_active = nullptr;
		}
		else
		{
			mp_active = mp_activeScenes->back();
		}
	}
}
