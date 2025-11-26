#include "pch.h"
#include "Application.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Time/TimeManager.h"
#include "Minty/Time/Timestep.h"
#include "Minty/Application/ApplicationInfo.h"

using namespace Minty;

Application* Minty::Application::s_instance = nullptr;

Minty::Application::Application(ApplicationInfo const &info)
: m_running(false)
, mp_window(nullptr)
, mp_memoryManager(nullptr)
, mp_jobManager(nullptr)
, mp_audioManager(nullptr)
, mp_layerManager(nullptr)
, mp_physicsManager(nullptr)
, mp_assetManager(nullptr)
, mp_inputManager(nullptr)
, mp_renderManager(nullptr)
, mp_sceneManager(nullptr)
, mp_timeManager(nullptr)
, m_managers()
, m_registeredSystems()
, m_registeredComponents()
{
	MINTY_ASSERT(s_instance == nullptr, ErrorCode::Singleton_AlreadyExists);
	s_instance = this;

	if(info.windowInfo)
	{
		mp_window = Window::create(*info.windowInfo);
	}

	if(info.memoryManagerInfo)
	{
		mp_memoryManager = MemoryManager::create(*info.memoryManagerInfo);
	}

	if(info.jobManagerInfo)
	{
		mp_jobManager = JobManager::create(*info.jobManagerInfo);
	}

	if(info.audioManagerInfo)
	{
		mp_audioManager = AudioManager::create(*info.audioManagerInfo);
	}

	if(info.layerManagerInfo)
	{
		mp_layerManager = LayerManager::create(*info.layerManagerInfo);
	}

	if(info.physicsManagerInfo)
	{
		mp_physicsManager = PhysicsManager::create(*info.physicsManagerInfo);
	}

	if(info.assetManagerInfo)
	{
		mp_assetManager = AssetManager::create(*info.assetManagerInfo);
	}

	if(info.inputManagerInfo)
	{
		mp_inputManager = InputManager::create(*info.inputManagerInfo);
	}

	if(info.renderManagerInfo)
	{
		mp_renderManager = RenderManager::create(*info.renderManagerInfo);
	}

	if(info.sceneManagerInfo)
	{
		mp_sceneManager = SceneManager::create(*info.sceneManagerInfo);
	}

	if(info.timeManagerInfo)
	{
		mp_timeManager = TimeManager::create(*info.timeManagerInfo);
	}
}

Minty::Application::~Application()
{
	MINTY_ASSERT(!m_running, ErrorCode::Object_InvalidState);
	MINTY_ASSERT(s_instance != nullptr, ErrorCode::Singleton_DoesNotExist);
	MINTY_ASSERT(s_instance == this, ErrorCode::Singleton_DifferentObject);

	Window::destroy(mp_window);
	MemoryManager::destroy(mp_memoryManager);
	JobManager::destroy(mp_jobManager);
	AudioManager::destroy(mp_audioManager);
	LayerManager::destroy(mp_layerManager);
	PhysicsManager::destroy(mp_physicsManager);
	AssetManager::destroy(mp_assetManager);
	InputManager::destroy(mp_inputManager);
	RenderManager::destroy(mp_renderManager);
	SceneManager::destroy(mp_sceneManager);
	TimeManager::destroy(mp_timeManager);

	s_instance = nullptr;
}

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::step()
{
	MINTY_TRACE_SCOPE();

	// finalize managers
	m_context->finalize();

	// render managers
	m_context->render();

	// process events
	m_context->process_events();

	// perform updates for frame and fixed updates
	Int const fixedUpdates = mp_timeManager->update();

	Timestep const time = mp_timeManager->get_frame_timestep();
	m_context->frame_update(time);

	for (Int i = 0; i < fixedUpdates; i++)
	{
		Timestep const fixedTime = mp_timeManager->get_fixed_timestep();
		m_context->fixed_update(fixedTime);
	}
}

void Minty::Application::run()
{
	// initialize
	m_context->initialize();

	// get the window and start running
	Window& window = m_context->get_window();

	mp_timeManager->start();

	// run the application loop
	m_running = true;
	while (m_running && window.is_open())
	{
		step();
	}
	m_running = false;

	mp_timeManager->stop();

	// if window is still open, close it
	if (window.is_open())
	{
		window.close();
	}

	// sync operations before moving on (threads, rendering, etc.)
	m_context->sync();

	// dispose the context
	m_context->dispose();
}

Owner<Application> Minty::Application::open(Path const& path)
{
	ApplicationInfo info{};
	info.context = Context::open(path);
	MINTY_ASSERT(info.context != nullptr, ErrorCode::File_NotFound, path);
	return create(info);
}

Owner<Application> Minty::Application::create(ApplicationInfo const& info)
{
	return Owner<Application>(info);
}

Window &Minty::Application::get_window() const
{
	MINTY_ASSERT(mp_window != nullptr, ErrorCode::Object_InvalidState);
	return *mp_window;
}

MemoryManager &Minty::Application::get_memory_manager() const
{
	MINTY_ASSERT(mp_memoryManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_memoryManager;
}

JobManager &Minty::Application::get_job_manager() const
{
	MINTY_ASSERT(mp_jobManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_jobManager;
}

AudioManager &Minty::Application::get_audio_manager() const
{
	MINTY_ASSERT(mp_audioManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_audioManager;
}

LayerManager &Minty::Application::get_layer_manager() const
{
	MINTY_ASSERT(mp_layerManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_layerManager;
}

PhysicsManager &Minty::Application::get_physics_manager() const
{
	MINTY_ASSERT(mp_physicsManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_physicsManager;
}

AssetManager &Minty::Application::get_asset_manager() const
{
	MINTY_ASSERT(mp_assetManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_assetManager;
}

InputManager &Minty::Application::get_input_manager() const
{
	MINTY_ASSERT(mp_inputManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_inputManager;
}

RenderManager &Minty::Application::get_render_manager() const
{
	MINTY_ASSERT(mp_renderManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_renderManager;
}

SceneManager &Minty::Application::get_scene_manager() const
{
	MINTY_ASSERT(mp_sceneManager != nullptr, ErrorCode::Object_InvalidState);
	return *mp_sceneManager;
}

TimeManager &Minty::Application::get_time_manager() const
{
    MINTY_ASSERT(mp_timeManager != nullptr, ErrorCode::Object_InvalidState);
    return *mp_timeManager;
}