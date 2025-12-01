#include "pch.h"
#include "Application.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Time/Timestep.h"
#include "Minty/Application/ApplicationInfo.h"

#include "Minty/Window/Window.h"
#include "Minty/Window/WindowInfo.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Memory/MemoryManagerInfo.h"
#include "Minty/Memory/MemoryStackInfo.h"
#include "Minty/Memory/MemoryPoolInfo.h"
#include "Minty/Job/JobManager.h"
#include "Minty/Job/JobManagerInfo.h"
#include "Minty/Audio/AudioManager.h"
#include "Minty/Audio/AudioManagerInfo.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Layer/LayerManagerInfo.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Physics/PhysicsManagerInfo.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Asset/AssetManagerInfo.h"
#include "Minty/Input/InputManager.h"
#include "Minty/Input/InputManagerInfo.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/RenderManagerInfo.h"
#include "Minty/Scene/SceneManager.h"
#include "Minty/Scene/SceneManagerInfo.h"
#include "Minty/Time/TimeController.h"
#include "Minty/Time/TimeControllerInfo.h"

using namespace Minty;

Application *Minty::Application::s_instance = nullptr;

Minty::Application::Application(ApplicationInfo const &info)
	: m_running(false), m_window(nullptr), m_memoryManager(nullptr), m_jobManager(nullptr), m_audioManager(nullptr), m_layerManager(nullptr), m_physicsManager(nullptr), m_assetManager(nullptr), m_inputManager(nullptr), m_renderManager(nullptr), m_sceneManager(nullptr), m_timeController(nullptr), m_managers(), m_registeredSystems(), m_registeredComponents()
{
	MINTY_ASSERT(s_instance == nullptr, ErrorCode::Singleton_AlreadyExists);
	s_instance = this;

	if (info.windowInfo)
	{
		m_window = Window::create(*info.windowInfo).to_shared();
		m_window->set_event_callback([this](Event &event)
									 { handle_event(event); });
	}

	if (info.memoryManagerInfo)
	{
		m_memoryManager = MemoryManager::create(*info.memoryManagerInfo);
		m_managers.add(m_memoryManager.get());
	}

	if (info.jobManagerInfo)
	{
		m_jobManager = JobManager::create(*info.jobManagerInfo);
		m_managers.add(m_jobManager.get());
	}

	if (info.audioManagerInfo)
	{
		m_audioManager = AudioManager::create(*info.audioManagerInfo);
		m_managers.add(m_audioManager.get());
	}

	if (info.layerManagerInfo)
	{
		m_layerManager = LayerManager::create(*info.layerManagerInfo);
		m_managers.add(m_layerManager.get());
	}

	if (info.physicsManagerInfo)
	{
		m_physicsManager = PhysicsManager::create(*info.physicsManagerInfo);
		m_managers.add(m_physicsManager.get());
	}

	if (info.assetManagerInfo)
	{
		m_assetManager = AssetManager::create(*info.assetManagerInfo);
		m_managers.add(m_assetManager.get());
	}

	if (info.inputManagerInfo)
	{
		m_inputManager = InputManager::create(*info.inputManagerInfo);
		m_managers.add(m_inputManager.get());
	}

	if (info.renderManagerInfo)
	{
		m_renderManager = RenderManager::create(*info.renderManagerInfo);
		m_managers.add(m_renderManager.get());
	}

	if (info.sceneManagerInfo)
	{
		m_sceneManager = SceneManager::create(*info.sceneManagerInfo);
		m_managers.add(m_sceneManager.get());
	}

	if (info.timeControllerInfo)
	{
		m_timeController = TimeController::create(*info.timeControllerInfo);
	}
}

Minty::Application::~Application()
{
	MINTY_ASSERT(!m_running, ErrorCode::Object_InvalidState);
	MINTY_ASSERT(s_instance != nullptr, ErrorCode::Singleton_DoesNotExist);
	MINTY_ASSERT(s_instance == this, ErrorCode::Singleton_DifferentObject);

	m_window.release();
	m_memoryManager.release();
	m_jobManager.release();
	m_audioManager.release();
	m_layerManager.release();
	m_physicsManager.release();
	m_assetManager.release();
	m_inputManager.release();
	m_renderManager.release();
	m_sceneManager.release();
	m_timeController.release();
	m_managers.clear();

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
	Int const fixedUpdates = m_timeController->update();

	Timestep const time = m_timeController->get_frame_timestep();
	m_context->frame_update(time);

	for (Int i = 0; i < fixedUpdates; i++)
	{
		Timestep const fixedTime = m_timeController->get_fixed_timestep();
		m_context->fixed_update(fixedTime);
	}
}

void Minty::Application::run()
{
	// initialize
	m_context->initialize();

	// get the window and start running
	Window &window = m_context->get_window();

	m_timeController->start();

	// run the application loop
	m_running = true;
	while (m_running && window.is_open())
	{
		step();
	}
	m_running = false;

	m_timeController->stop();

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

Unique<Application> Minty::Application::open(Path const &path)
{
	ApplicationInfo info{};

	// check if the path is valid
	MINTY_ASSERT(!path.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(path.has_extension(".minty"), ErrorCode::Argument_InvalidFormat);
	MINTY_ASSERT(Path::exists(path), ErrorCode::File_NotFound);
	MINTY_ASSERT(Path::is_file(path), ErrorCode::File_NotAFile);

	// read the file
	PhysicalFile file(path, File::Flags::Read);
	MINTY_ASSERT(file.is_open(), ErrorCode::File_FailedToOpen, path);

	// open a reader
	TextFileReader reader(&file);

	// create the infos
	WindowInfo windowInfo{};
	MemoryManagerInfo memoryManagerInfo{};
	Vector<MemoryStackInfo> stackInfos;
	Vector<MemoryPoolInfo> poolInfos;
	JobManagerInfo jobManagerInfo{};
	AudioManagerInfo audioManagerInfo{};
	LayerManagerInfo layerManagerInfo{};
	PhysicsManagerInfo physicsManagerInfo{};
	AssetManagerInfo assetManagerInfo{};
	InputManagerInfo inputManagerInfo{};
	RenderManagerInfo renderManagerInfo{};
	SceneManagerInfo sceneManagerInfo{};
	TimeControllerInfo timeControllerInfo{};

	// read the infos
	if (reader.indent("Window"))
	{
		reader.read("Position", windowInfo.position);
		reader.read("Size", windowInfo.size);
		reader.read("Title", windowInfo.title);
		reader.read("Icon", windowInfo.icon);
		reader.outdent();

		info.windowInfo = &windowInfo;
	}
	if (reader.indent("Memory"))
	{
		ULong tempFrame;
		if (reader.read("Frame", tempFrame))
		{
			MemoryStackInfo stackInfo{};
			stackInfo.capacity = tempFrame;
			stackInfos.add(stackInfo);
			memoryManagerInfo.frameStackInfo = &stackInfos.back();
		}
		ULong2 tempTask;
		if (reader.read("Task", tempTask))
		{
			MemoryStackInfo stackInfo{};
			stackInfo.capacity = tempTask.x;
			memoryManagerInfo.taskStackCount = tempTask.y;
			stackInfos.add(stackInfo);
			memoryManagerInfo.taskStackInfo = &stackInfos.back();
		}
		Vector<ULong2> tempPersistent;
		if (reader.read("Persistent", tempPersistent))
		{
			MemoryPoolInfo poolInfo{};
			poolInfos.reserve(tempPersistent.get_size());
			for (ULong2 const &persistent : tempPersistent)
			{
				poolInfo.blockSize = static_cast<Size>(persistent.x);
				poolInfo.blockCount = static_cast<Size>(persistent.y);
				poolInfos.add(poolInfo);
			}
			memoryManagerInfo.persistentPoolInfos = poolInfos.get_data();
			memoryManagerInfo.persistentPoolInfoCount = poolInfos.get_size();
		}
		reader.outdent();

		info.memoryManagerInfo = &memoryManagerInfo;
	}
	if (reader.indent("Job"))
	{
		reader.read("Threads", jobManagerInfo.threadCount);
		reader.outdent();

		info.jobManagerInfo = &jobManagerInfo;
	}
	if (reader.indent("Audio"))
	{
		reader.outdent();

		info.audioManagerInfo = &audioManagerInfo;
	}
	if (reader.indent("Layer"))
	{
		if (reader.indent("Layers"))
		{
			layerManagerInfo.layerCollisions.clear();
			layerManagerInfo.layerCollisions.reserve(reader.get_size());

			String name;
			Int2 layer;
			for (Size i = 0; i < reader.get_size(); i++)
			{
				// read layer name
				if (!reader.read_name(i, name))
				{
					MINTY_ABORT(ErrorCode::Serialization_InvalidFormat);
				}
				// read layer data
				if (!reader.read(i, layer))
				{
					MINTY_ABORT(ErrorCode::Serialization_InvalidFormat);
				}

				// add the layer collision
				layerManagerInfo.layerCollisions.add(
					{name, layer.x, layer.y});
			}
			reader.outdent();
		}
		reader.outdent();

		info.layerManagerInfo = &layerManagerInfo;
	}
	if (reader.indent("Physics"))
	{
		reader.outdent();

		info.physicsManagerInfo = &physicsManagerInfo;
	}
	if (reader.indent("Asset"))
	{
		reader.read("SavePaths", assetManagerInfo.savePaths);
		reader.read("Wraps", assetManagerInfo.wraps);
		reader.outdent();

		info.assetManagerInfo = &assetManagerInfo;
	}
	if (reader.indent("Input"))
	{
		reader.outdent();

		info.inputManagerInfo = &inputManagerInfo;
	}
	if (reader.indent("Render"))
	{
		reader.read("TargetFormat", renderManagerInfo.targetSurfaceFormat);
		reader.outdent();

		info.renderManagerInfo = &renderManagerInfo;
	}
	if (reader.indent("Scene"))
	{
		reader.read("Initial", sceneManagerInfo.initialScene);
		reader.outdent();

		info.sceneManagerInfo = &sceneManagerInfo;
	}

	return create(info);
}

Unique<Application> Minty::Application::create(ApplicationInfo const &info)
{
	return Unique<Application>::create(info);
}

void Minty::Application::handle_event(Event &event)
{
	// pass the event to the managers
	for (Manager *const manager : m_managers)
	{
		manager->handle_event(event);

		// if event was processed, stop propagating
		if (event.is_processed())
		{
			break;
		}
	}
}