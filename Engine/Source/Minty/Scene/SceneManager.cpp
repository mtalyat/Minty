#include "pch.h"
#include "SceneManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Job/JobManager.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Scene/SceneInfo.h"
#include "Minty/Scene/SceneManagerInfo.h"

using namespace Minty;

Minty::SceneManager::SceneManager(SceneManagerInfo const &info)
	: Manager(), m_initialScene(info.initialScene), m_scenes(), m_activeScene(nullptr), m_nextScene(nullptr)
{
	MINTY_ASSERT_F(m_initialScene.is_empty() || Path::exists(m_initialScene), ErrorCode::Argument_InvalidValue, m_initialScene);

	// load the initial scene, if not loaded
	if (!m_initialScene.is_empty())
	{
		// load
		Ref<Scene> scene = load(m_initialScene, true);
	}
}

Minty::SceneManager::~SceneManager()
{
	// unload the active scene, if any
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_unload();
	}
}

void Minty::SceneManager::set_active(Ref<Scene> const &scene)
{
	m_nextScene = scene;
}

Ref<Scene> Minty::SceneManager::load(Path const &path, Bool const setAsActive)
{
	AssetManager &assetManager = AssetManager::get_singleton();

	SceneInfo info{};
	info.id = assetManager.read_id(path);
	info.name = path.get_name().get_string();

	// create empty scene
	Shared<Scene> scene = Scene::create(info);

	// deserialize the Scene
	if (Unique<Reader> const reader = assetManager.open_reader(path))
	{
		// deserialize the scene
		Serializer<Scene>::deserialize(*reader, *scene);
	}

	// add the Scene
	m_scenes.add(scene->get_id(), {scene, path});

	Ref<Scene> const sceneRef = scene.to_ref();

	// set as active if requested
	if (setAsActive)
	{
		set_active(sceneRef);
	}

	return sceneRef;
}

Ref<Scene> Minty::SceneManager::load(Shared<Scene> const &scene, Bool const setAsActive)
{
	// add the Scene
	m_scenes.add(scene->get_id(), {scene, ""});

	Ref<Scene> sceneRef = scene.to_ref();

	// set as active if requested
	if (setAsActive)
	{
		set_active(sceneRef);
	}

	return sceneRef;
}

void Minty::SceneManager::unload(UUID const id)
{
	MINTY_ASSERT_F(contains(id), ErrorCode::Argument_KeyNotFound, id);

	// get the scene
	Shared<Scene> scene = m_scenes.at(id).scene;

	// remove it
	m_scenes.remove(id);

	// if it is the active scene, set the active scene to null
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_unload();
		m_activeScene.release();
	}

	// done
	scene.release();
}

void Minty::SceneManager::reload(UUID const id)
{
	MINTY_ASSERT_F(contains(id), ErrorCode::Argument_KeyNotFound, id);

	// get the scene data
	SceneData &sceneData = m_scenes.at(id);

	// get the path to the scene
	Path const &path = sceneData.path;

	// get the scene
	Shared<Scene> &scene = sceneData.scene;

	// open the file
	AssetManager &assetManager = AssetManager::get_singleton();
	if(Unique<Reader> const reader = assetManager.open_reader(path))
	{
		Serializer<Scene>::deserialize(*reader, *scene);
	}

	// TODO: implement deserialization for all asset types
	// TODO: reload all assets within the scene
	//// reload all assets within the scene
	// for (UUID const assetId : scene->get_loaded_assets())
	//{
	//	// reload the asset
	//	assetManager.reload(assetId);
	// }
}

UUID Minty::SceneManager::schedule_load(Path const &path, Job const &onCompletion, Bool const setAsActive)
{
	JobManager &jobManager = JobManager::get_singleton();
	jobManager.schedule([this, path, onCompletion, setAsActive]()
						{
			// load the scene
			Ref<Scene> scene = load(path, setAsActive);

			// run the completion job
			onCompletion(); });
	return AssetManager::get_singleton().read_id(path);
}

void Minty::SceneManager::schedule_unload(UUID const id, Job const &onCompletion)
{
	MINTY_ASSERT_F(m_scenes.contains(id), ErrorCode::Argument_KeyNotFound, id);

	JobManager &jobManager = JobManager::get_singleton();
	jobManager.schedule([this, id, onCompletion]()
						{
			// unload the scene
			unload(id);

			// run the completion job
			onCompletion(); });
}

void Minty::SceneManager::frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// update the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_frame_update(time);
	}
	else
	{
		MINTY_LOG_WARNING("No active Scene.");
	}
}

void Minty::SceneManager::fixed_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// update the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_fixed_update(time);
	}
	else
	{
		MINTY_LOG_WARNING("No active Scene.");
	}
}

void Minty::SceneManager::finalize()
{
	MINTY_TRACE_SCOPE();

	// finalize the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_finalize();
	}

	refresh();
}

void Minty::SceneManager::render()
{
	MINTY_TRACE_SCOPE();

	// render the active scene
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_render();
	}
}

void Minty::SceneManager::handle_event(Event &event)
{
	MINTY_TRACE_SCOPE();

	// pass the event on to each of the systems
	if (m_activeScene != nullptr)
	{
		m_activeScene->on_event(event);
	}
}

void Minty::SceneManager::refresh()
{
	// move to the next active Scene
	if (m_nextScene != nullptr)
	{
		if (m_activeScene != nullptr)
		{
			m_activeScene->on_unload();
		}
		m_activeScene = m_nextScene;
		m_nextScene.release();
		if (m_activeScene != nullptr)
		{
			m_activeScene->on_load();
		}
	}
}

Unique<SceneManager> Minty::SceneManager::create(SceneManagerInfo const &info)
{
	return Unique<SceneManager>::create(info);
}

Unique<SceneManager> Minty::SceneManager::create()
{
	SceneManagerInfo info{};
	return create(info);
}

Unique<SceneManager> const& Minty::SceneManager::get_instance()
{
	return Application::get_singleton().get_scene_manager();
}

SceneManager& Minty::SceneManager::get_singleton()
{
	Unique<SceneManager> const& instance = Application::get_singleton().get_scene_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_SceneManagerNotInitialized);
	return *instance;
}
