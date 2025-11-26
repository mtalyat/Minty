#include "pch.h"
#include "Context.h"
#include "Minty/Component/_Component.h"
#include "Minty/System/_System.h"
#include "Minty/Event/_Event.h"
#include "Minty/File/PhysicalFile.h"
#include "Minty/Debug/Trace.h"

using namespace Minty;

Context* Context::s_instance = nullptr;

/// <summary>
/// Creates a new Context using the given ContextInfo.
/// </summary>
/// <param name="info">The input arguments.</param>
Minty::Context::Context(ContextInfo const& info)
	: m_initialized(false)
	, m_window(nullptr)
	, m_memoryManager(nullptr)
	, m_jobManager(nullptr)
	, m_audioManager(nullptr)
	, m_layerManager(nullptr)
	, m_physicsManager(nullptr)
	, m_assetManager(nullptr)
	, m_inputManager(nullptr)
	, m_renderManager(nullptr)
	, m_sceneManager(nullptr)
	, m_managers()
	, m_registeredSystems()
	, m_registeredComponents()
{
	// set instance
	MINTY_ASSERT(!s_instance, ErrorCode::Singleton_AlreadyExists);
	s_instance = this;

	// register systems and components
	register_systems();
	register_components();

	// create window 
	m_window = Window::create(info.windowInfo);

	// create managers
	m_memoryManager = MemoryManager::create(info.memoryManagerInfo);
	m_jobManager = JobManager::create(info.jobManagerInfo);
	m_audioManager = AudioManager::create(info.audioManagerInfo);
	m_layerManager = LayerManager::create(info.layerManagerInfo);
	m_physicsManager = PhysicsManager::create(info.physicsManagerInfo);
	m_assetManager = AssetManager::create(info.assetManagerInfo);
	m_inputManager = InputManager::create(info.inputManagerInfo);
	m_renderManager = RenderManager::create(info.renderManagerInfo);
	m_sceneManager = SceneManager::create(info.sceneManagerInfo);
	m_managers.add(m_memoryManager.get());
	m_managers.add(m_jobManager.get());
	m_managers.add(m_renderManager.get());
	m_managers.add(m_audioManager.get());
	m_managers.add(m_layerManager.get());
	m_managers.add(m_physicsManager.get());
	m_managers.add(m_assetManager.get());
	m_managers.add(m_inputManager.get());
	m_managers.add(m_sceneManager.get());

	// set the window event callback function
	m_window->set_event_callback([this](Event& event) {
		handle_event(event);
		});
}


/// <summary>
/// Moves the given Context.
/// </summary>
/// <param name="other">The Context to move.</param>
Minty::Context::Context(Context&& other) noexcept
	: m_initialized(other.m_initialized)
	, m_window(std::move(other.m_window))
	, m_memoryManager(std::move(other.m_memoryManager))
	, m_jobManager(std::move(other.m_jobManager))
	, m_audioManager(std::move(other.m_audioManager))
	, m_layerManager(std::move(other.m_layerManager))
	, m_physicsManager(std::move(other.m_physicsManager))
	, m_assetManager(std::move(other.m_assetManager))
	, m_inputManager(std::move(other.m_inputManager))
	, m_renderManager(std::move(other.m_renderManager))
	, m_sceneManager(std::move(other.m_sceneManager))
	, m_managers(std::move(other.m_managers))
	, m_registeredSystems(std::move(other.m_registeredSystems))
	, m_registeredComponents(std::move(other.m_registeredComponents))
{
	other.m_initialized = false;
}

Minty::Context::~Context()
{
	MINTY_ASSERT(!m_initialized, ErrorCode::Object_NeverDisposed);

	// clean up
	s_instance = nullptr;
}

Context& Minty::Context::operator=(Context&& other) noexcept
{
	if (this != &other)
	{
		m_memoryManager = std::move(other.m_memoryManager);
		m_jobManager = std::move(other.m_jobManager);
		m_audioManager = std::move(other.m_audioManager);
		m_layerManager = std::move(other.m_layerManager);
		m_physicsManager = std::move(other.m_physicsManager);
		m_assetManager = std::move(other.m_assetManager);
		m_renderManager = std::move(other.m_renderManager);
		m_sceneManager = std::move(other.m_sceneManager);
		m_managers = std::move(other.m_managers);
		m_registeredSystems = std::move(other.m_registeredSystems);
		m_registeredComponents = std::move(other.m_registeredComponents);
	}
	return *this;
}

void Minty::Context::register_components()
{
	register_component<AnimatorComponent>("Animator");
	register_component<AudioListenerComponent>("AudioListener");
	register_component<AudioSourceComponent>("AudioSource");
	register_component<CameraComponent>("Camera");
	register_component<CanvasComponent>("Canvas");
	register_component<ColliderComponent>("Collider");
	register_component<EnabledComponent>("Enabled");
	register_component<LayerComponent>("Layer");
	register_component<MaskComponent>("Mask");
	register_component<MaskedComponent>("Masked");
	register_component<MeshComponent>("Mesh");
	register_component<NameComponent>("Name");
	register_component<RelationshipComponent>("Relationship");
	register_component<RigidBodyComponent>("RigidBody");
	register_component<SpriteComponent>("Sprite");
	register_component<TextComponent>("Text");
	register_component<TransformComponent>("Transform");
	register_component<UITransformComponent>("UITransform");
	register_component<UUIDComponent>("UUID");
	register_component<VisibleComponent>("Visible");
}

void Minty::Context::register_systems()
{
	register_system<AnimationSystem>("Animation", 1);
	register_system<AudioSystem>("Audio", 1);
	register_system<PhysicsSystem>("Physics", -100);
	register_system<RenderSystem>("Render", 100);
}

void Minty::Context::initialize()
{
	MINTY_ASSERT(!m_initialized, ErrorCode::Object_AlreadyInitialized);

	// initialize the managers
	for (Manager* manager : m_managers)
	{
		manager->initialize();
	}

	// make sure the scene manager is refreshed to load the initial scene
	m_sceneManager->refresh();

	m_initialized = true;
}

void Minty::Context::dispose()
{
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);

	// dispose window
	m_window.release();

	// dispose managers
	for (auto it = m_managers.rbegin(); it != m_managers.rend(); ++it)
	{
		(*it)->dispose();
	}
	m_managers.clear();

	// unregister systems and components
	m_registeredSystems.clear();
	m_registeredComponents.clear();

	m_initialized = false;
}

void Minty::Context::frame_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	// update managers
	for (Manager* manager : m_managers)
	{
		manager->frame_update(time);
	}
}

void Minty::Context::fixed_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	// fixed update managers
	for (Manager* manager : m_managers)
	{
		manager->fixed_update(time);
	}
}

void Minty::Context::finalize()
{
	MINTY_TRACE_SCOPE();

	// finalize managers
	for (Manager* manager : m_managers)
	{
		manager->finalize();
	}
}

void Minty::Context::render()
{
	MINTY_TRACE_SCOPE();

	// start rendering
	if (!m_renderManager->start_frame())
	{
		return;
	}

	// render managers
	for (Manager* manager : m_managers)
	{
		manager->render();
	}

	// stop rendering
	m_renderManager->end_frame();

	MINTY_TRACE_FRAME();
}

void Minty::Context::sync()
{
	MINTY_TRACE_SCOPE();

	// sync window
	m_window->sync();

	// sync managers
	for (Manager* manager : m_managers)
	{
		manager->sync();
	}
}

void Minty::Context::process_events()
{
	MINTY_TRACE_SCOPE();

	m_window->process_events();
}

void Minty::Context::handle_event(Event& event)
{
	// pass event on to the managers
	for (Manager* manager : m_managers)
	{
		manager->handle_event(event);

		// if the event was processed, break
		if (event.is_processed())
		{
			break;
		}
	}
}

SystemData const& Minty::Context::get_system_info(String const& name) const
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);
	MINTY_ASSERT(m_registeredSystems.contains(name), ErrorCode::System_NotRegistered, name);
	return m_registeredSystems.at(name);
}

SystemData const& Minty::Context::get_system_info(TypeID const& typeId) const
{
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);
	MINTY_ASSERT(m_registeredSystems.contains(typeId), ErrorCode::System_NotRegistered, typeId.name());
	return m_registeredSystems.at(typeId);
}

ComponentData const& Minty::Context::get_component_info(String const& name) const
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);
	MINTY_ASSERT(m_registeredComponents.contains(name), ErrorCode::Component_NotRegistered, name);
	return m_registeredComponents.at(name);
}

ComponentData const& Minty::Context::get_component_info(TypeID const& typeId) const
{
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);
	MINTY_ASSERT(m_registeredComponents.contains(typeId), ErrorCode::Component_NotRegistered, typeId.name());
	return m_registeredComponents.at(typeId);
}

Owner<Context> Minty::Context::open(Path const& path)
{
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

	// create the info
	ContextInfo info{};
	if (reader.indent("Window"))
	{
		reader.read("Position", info.windowInfo.position);
		reader.read("Size", info.windowInfo.size);
		reader.read("Title", info.windowInfo.title);
		reader.read("Icon", info.windowInfo.icon);

		reader.outdent();
	}
	if (reader.indent("Memory"))
	{
		ULong tempTemporary;
		if (reader.read("Temporary", tempTemporary))
		{
			info.memoryManagerInfo.temporary.capacity = tempTemporary;
		}
		ULong2 tempTask;
		if (reader.read("Task", tempTask))
		{
			info.memoryManagerInfo.task.capacity = tempTask.x;
			info.memoryManagerInfo.taskCount = tempTask.y;
		}
		Vector<ULong2> tempPersistent;
		if (reader.read("Persistent", tempPersistent))
		{
			info.memoryManagerInfo.persistents.clear();
			info.memoryManagerInfo.persistents.reserve(tempPersistent.get_size());
			for (ULong2 const& persistent : tempPersistent)
			{
				info.memoryManagerInfo.persistents.add(MemoryPoolInfo{
					static_cast<Size>(persistent.x), 
					static_cast<Size>(persistent.y)
				});
			}
		}

		reader.outdent();
	}
	if (reader.indent("Job"))
	{
		reader.read("Threads", info.jobManagerInfo.threadCount);

		reader.outdent();
	}
	if (reader.indent("Audio"))
	{
		reader.outdent();
	}
	if (reader.indent("Layer"))
	{
		if (reader.indent("Layers"))
		{
			info.layerManagerInfo.layerCollisions.clear();
			info.layerManagerInfo.layerCollisions.reserve(reader.get_size());

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
				info.layerManagerInfo.layerCollisions.add(
					{ name, layer.x, layer.y }
				);
			}

			reader.outdent();
		}

		reader.outdent();
	}
	if (reader.indent("Physics"))
	{
		reader.outdent();
	}
	if (reader.indent("Asset"))
	{
		reader.read("SavePaths", info.assetManagerInfo.savePaths);
		reader.read("Wraps", info.assetManagerInfo.wraps);

		reader.outdent();
	}
	if (reader.indent("Input"))
	{
		reader.outdent();
	}
	if (reader.indent("Render"))
	{
		reader.read("TargetFormat", info.renderManagerInfo.targetSurfaceFormat);

		reader.outdent();
	}
	if (reader.indent("Scene"))
	{
		reader.read("Initial", info.sceneManagerInfo.initialScene);

		reader.outdent();
	}

	return create(info);
}

Owner<Context> Minty::Context::create(ContextInfo const& info)
{
	return Owner<Context>(info);
}
