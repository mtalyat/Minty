#include "pch.h"
#include "SceneManager.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

void Minty::SceneManager::set_active(Ref<Scene> const& scene)
{
	m_nextScene = scene;
}

void Minty::SceneManager::add(Ref<Scene> const& scene)
{
	// add to the list of scenes
	m_scenes.add(scene);

	// set to active if not set
	if (m_activeScene == nullptr)
	{
		m_activeScene = scene;
	}
}

void Minty::SceneManager::remove(Ref<Scene> const& scene)
{
	// remove from the list of scenes
	m_scenes.remove(scene);

	// set to null if it was the active scene
	if (m_activeScene == scene)
	{
		m_activeScene = nullptr;
	}
}

Ref<Scene> Minty::SceneManager::load(Path const& path)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// load the scene
	Ref<Scene> scene = assetManager.load<Scene>(path);

	MINTY_ASSERT(scene != nullptr, F("Failed to load Scene at path: {}", path));

	// add the Scene
	add(scene);

	return scene;
}

void Minty::SceneManager::unload(UUID const id)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// get the scene
	Ref<Scene> scene = assetManager.at<Scene>(id);

	// remove the scene
	remove(scene);

	// unload the scene
	assetManager.unload(id);
}

UUID Minty::SceneManager::schedule_load(Path const& path, Job const& onCompletion)
{
	AssetManager& assetManager = AssetManager::get_singleton();
	return assetManager.schedule_load(path, [this, onCompletion](AssetManager& assetManager, UUID const id)
		{
			// get the scene
			Ref<Scene> scene = assetManager.get<Scene>(id);
			MINTY_ASSERT(scene != nullptr, F("Failed to load Scene with ID: {}", id));
			// add the scene
			add(scene);
			// run the completion job
			onCompletion();
		});
}

void Minty::SceneManager::schedule_unload(UUID const id, Job const& onCompletion)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// get the scene
	Ref<Scene> scene = assetManager.at<Scene>(id);

	// remove the scene
	remove(scene);

	assetManager.schedule_unload(id, [this, onCompletion](AssetManager& assetManager, UUID const id)
		{
			// run the completion job
			onCompletion();
		});
}

void Minty::SceneManager::initialize()
{
	// load the initial scene, if not loaded
	if (!m_initialScene.is_empty())
	{
		// load
		Ref<Scene> scene = load(m_initialScene);
		
		// set as active
		m_activeScene = scene;
	}

	// load all of the scenes
	for (Ref<Scene> const& scene : m_scenes)
	{
		scene->on_load();
	}

	Manager::initialize();
}

void Minty::SceneManager::dispose()
{
	// unload all of the scenes
	for (Ref<Scene> const& scene : m_scenes)
	{
		if (scene != nullptr)
		{
			scene->on_unload();
		}
	}

	// clear the list of scenes
	m_scenes.clear();
	m_activeScene = nullptr;
	m_nextScene = nullptr;

	Manager::dispose();
}

void Minty::SceneManager::update(Time const& time)
{
	// update the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_update(time);
	}
}

void Minty::SceneManager::finalize()
{
	// finalize the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_finalize();
	}

	// move to the next active Scene
	if (m_nextScene != nullptr)
	{
		m_activeScene = m_nextScene;
		m_nextScene = nullptr;
	}
}

void Minty::SceneManager::render()
{
	// render the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_render();
	}
}

void Minty::SceneManager::sync()
{

}

void Minty::SceneManager::handle_event(Event& event)
{
	// pass the event on to each of the systems
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_event(event);
	}
}

Owner<SceneManager> Minty::SceneManager::create(SceneManagerBuilder const& builder)
{
	return Owner<SceneManager>(builder);
}

SceneManager& Minty::SceneManager::get_singleton()
{
	return Context::get_singleton().get_scene_manager();
}
