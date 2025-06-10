#include "pch.h"
#include "SceneManager.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

void Minty::SceneManager::set_active(Ref<Scene> const& scene)
{
	m_nextScene = scene;
}

Ref<Scene> Minty::SceneManager::load(Path const& path, Bool const setAsActive)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	SceneBuilder builder{};
	builder.id = assetManager.read_id(path);
	builder.name = path.get_name().get_string();

	// create empty scene
	Owner<Scene> scene = Scene::create(builder);

	// deserialize the Scene
	Reader* reader;
	if (assetManager.open_reader(path, reader))
	{
		// deserialize the scene
		scene->deserialize(*reader);

		// close the reader
		assetManager.close_reader(reader);
	}

	// add the Scene
	m_scenes.add(scene->get_id(), {scene, path});

	Ref<Scene> sceneRef = scene.create_ref();

	// set as active if requested
	if (setAsActive)
	{
		set_active(sceneRef);
	}

	return sceneRef;
}

void Minty::SceneManager::unload(UUID const id)
{
	MINTY_ASSERT(contains(id), "Cannot unload Scene. The SceneManager does not contain a Scene with the given ID.");

	// get the scene
	Owner<Scene> scene = m_scenes.at(id).scene;

	// remove it
	m_scenes.remove(id);

	// if it is the active scene, set the active scene to null
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_unload();
		m_activeScene = nullptr;
	}

	// done
	scene.release();
}

void Minty::SceneManager::reload(UUID const id)
{
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");

	// get the scene data
	SceneData& sceneData = m_scenes.at(id);

	// get the path to the scene
	Path const& path = sceneData.path;

	// get the scene
	Owner<Scene>& scene = sceneData.scene;

	// open the file
	AssetManager& assetManager = AssetManager::get_singleton();
	Reader* reader = nullptr;
	if (!assetManager.open_reader(path, reader))
	{
		MINTY_ABORT(F("Failed to reload asset: {}. Could not open file.", path));
		return;
	}

	// deserialize the asset again
	if (!scene->deserialize(*reader))
	{
		MINTY_ABORT(F("Failed to deserialize asset: {}. Failed to deserialize the data.", path));
		assetManager.close_reader(reader);
		return;
	}

	// close the reader
	assetManager.close_reader(reader);
}

UUID Minty::SceneManager::schedule_load(Path const& path, Job const& onCompletion, Bool const setAsActive)
{
	JobManager& jobManager = JobManager::get_singleton();
	jobManager.schedule([this, path, onCompletion, setAsActive]()
		{
			// load the scene
			Ref<Scene> scene = load(path, setAsActive);

			// run the completion job
			onCompletion();
		});
	return AssetManager::get_singleton().read_id(path);
}

void Minty::SceneManager::schedule_unload(UUID const id, Job const& onCompletion)
{
	MINTY_ASSERT(m_scenes.contains(id), "Cannot schedule unload. The SceneManager does not contain a Scene with the given ID.");

	JobManager& jobManager = JobManager::get_singleton();
	jobManager.schedule([this, id, onCompletion]()
		{
			// unload the scene
			unload(id);

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
		Ref<Scene> scene = load(m_initialScene, true);
	}

	Manager::initialize();
}

void Minty::SceneManager::dispose()
{
	// unload the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_unload();
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
		if (m_activeScene != nullptr)
		{
			m_activeScene->on_unload();
		}
		m_activeScene = m_nextScene;
		m_nextScene = nullptr;
		if (m_activeScene != nullptr)
		{
			m_activeScene->on_load();
		}
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
