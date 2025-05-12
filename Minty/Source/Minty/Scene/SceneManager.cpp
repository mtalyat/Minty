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

void Minty::SceneManager::load(Path const& path)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// load the scene
	Ref<Scene> scene = assetManager.load<Scene>(path);

	// add the Scene
	add(scene);
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

void Minty::SceneManager::schedule_load(Path const& path, Job const& onCompletion)
{
	AssetManager& assetManager = AssetManager::get_singleton();
	

	// load the scene
	
}

void Minty::SceneManager::schedule_unload(UUID const id, Job const& onCompletion)
{
}

void Minty::SceneManager::initialize()
{
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
		scene->on_unload();
	}

	// clear the list of scenes
	m_scenes.clear();
	m_activeScene = nullptr;

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

Owner<SceneManager> Minty::SceneManager::create(SceneManagerBuilder const& builder)
{
	return Owner<SceneManager>(builder);
}

SceneManager& Minty::SceneManager::get_singleton()
{
	return Context::get_singleton().get_scene_manager();
}
