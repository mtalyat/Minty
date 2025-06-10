#include "pch.h"
#include "Context.h"
#include "Minty/Component/_Component.h"
#include "Minty/System/_System.h"
#include "Minty/Event/_Event.h"
#include "Minty/File/PhysicalFile.h"

using namespace Minty;

Context* Context::s_instance = nullptr;

/// <summary>
/// Creates a new Context using the given ContextBuilder.
/// </summary>
/// <param name="builder">The input arguments.</param>
Minty::Context::Context(ContextBuilder const& builder)
	: m_initialized(false)
	, mp_dualBuffer(nullptr)
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
	MINTY_ASSERT(!s_instance, "Context singleton already exists.");
	s_instance = this;
	
	// initialize dual buffering if a debug log path was given
	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}

	// register systems and components
	register_systems();
	register_components();

	// create window 
	m_window = Window::create(builder.windowBuilder);

	// create managers
	m_memoryManager = MemoryManager::create(builder.memoryManagerBuilder);
	m_jobManager = JobManager::create(builder.jobManagerBuilder);
	m_audioManager = AudioManager::create(builder.audioManagerBuilder);
	m_layerManager = LayerManager::create(builder.layerManagerBuilder);
	m_physicsManager = PhysicsManager::create(builder.physicsManagerBuilder);
	m_assetManager = AssetManager::create(builder.assetManagerBuilder);
	m_inputManager = InputManager::create(builder.inputManagerBuilder);
	m_renderManager = RenderManager::create(builder.renderManagerBuilder);
	m_sceneManager = SceneManager::create(builder.sceneManagerBuilder);
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
	, mp_dualBuffer(other.mp_dualBuffer)
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
	other.mp_dualBuffer = nullptr;
}

Minty::Context::~Context()
{
	MINTY_ASSERT_ERROR(!m_initialized, "Context was destroyed before it was disposed.");

	// clean up
	delete mp_dualBuffer;
	s_instance = nullptr;
}

Context& Minty::Context::operator=(Context&& other) noexcept
{
	if (this != &other)
	{
		mp_dualBuffer = other.mp_dualBuffer;
		other.mp_dualBuffer = nullptr;
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
	MINTY_ASSERT(!m_initialized, "Context was already initialized.");

	// initialize the managers
	for (Manager* manager : m_managers)
	{
		manager->initialize();
	}

	m_initialized = true;
}

void Minty::Context::dispose()
{
	MINTY_ASSERT(m_initialized, "Context was not initialized.");

	// dispose managers
	for (auto it = m_managers.rbegin(); it != m_managers.rend(); ++it)
	{
		(*it)->dispose();
	}
	m_managers.clear();

	// unregister systems
	m_registeredSystems.clear();

	m_initialized = false;
}

void Minty::Context::update(Time const& time)
{
	// update managers
	for (Manager* manager : m_managers)
	{
		manager->update(time);
	}
}

void Minty::Context::finalize()
{
	// finalize managers
	for (Manager* manager : m_managers)
	{
		manager->finalize();
	}
}

void Minty::Context::render()
{
	// start rendering
	m_renderManager->start_frame();

	// render managers
	for (Manager* manager : m_managers)
	{
		manager->render();
	}

	// stop rendering
	m_renderManager->end_frame();
}

void Minty::Context::sync()
{
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

SystemInfo const* Minty::Context::get_system_info(String const& name) const
{
	auto it = m_registeredSystems.find(name);
	if (it == m_registeredSystems.end())
	{
		return nullptr;
	}
	return &it->get_third();
}

SystemInfo const* Minty::Context::get_system_info(TypeID const& typeId) const
{
	auto it = m_registeredSystems.find(typeId);
	if (it == m_registeredSystems.end())
	{
		return nullptr;
	}
	return &it->get_third();
}

ComponentInfo const* Minty::Context::get_component_info(String const& name) const
{
	auto it = m_registeredComponents.find(name);
	if (it == m_registeredComponents.end())
	{
		return nullptr;
	}
	return &it->get_third();
}

ComponentInfo const* Minty::Context::get_component_info(TypeID const& typeId) const
{
	auto it = m_registeredComponents.find(typeId);
	if (it == m_registeredComponents.end())
	{
		return nullptr;
	}
	return &it->get_third();
}

Owner<Context> Minty::Context::open(Path const& path)
{
	// check if the path is valid
	MINTY_ASSERT(!path.is_empty(), "Path to context file is empty.");
	MINTY_ASSERT(path.has_extension(".minty"), "Context file must have a .minty extension.");
	MINTY_ASSERT(Path::exists(path), F("Context file does not exist: {}", path));
	MINTY_ASSERT(Path::is_file(path), F("Context file is not a file: {}", path));

	// read the file
	PhysicalFile file(path, File::Flags::Read);

	MINTY_ASSERT(file.is_open(), F("Failed to open context file: {}", path));

	// open a reader
	TextFileReader reader(&file);

	// create the builder
	ContextBuilder builder{};
	if (reader.indent("Window"))
	{
		reader.read("Position", builder.windowBuilder.position);
		reader.read("Size", builder.windowBuilder.size);
		reader.read("Title", builder.windowBuilder.title);

		reader.outdent();
	}
	if (reader.indent("Memory"))
	{
		ULong tempTemporary;
		if (reader.read("Temporary", tempTemporary))
		{
			builder.memoryManagerBuilder.temporary.capacity = tempTemporary;
		}
		ULong2 tempTask;
		if (reader.read("Task", tempTask))
		{
			builder.memoryManagerBuilder.task.capacity = tempTask.x;
			builder.memoryManagerBuilder.taskCount = tempTask.y;
		}
		Vector<ULong2> tempPersistent;
		if (reader.read("Persistent", tempPersistent))
		{
			builder.memoryManagerBuilder.persistents.clear();
			builder.memoryManagerBuilder.persistents.reserve(tempPersistent.get_size());
			for (ULong2 const& persistent : tempPersistent)
			{
				builder.memoryManagerBuilder.persistents.add(MemoryPoolBuilder(persistent.x, persistent.y));
			}
		}

		reader.outdent();
	}
	if (reader.indent("Job"))
	{
		reader.read("Threads", builder.jobManagerBuilder.threadCount);

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
			builder.layerManagerBuilder.layerCollisions.clear();
			builder.layerManagerBuilder.layerCollisions.reserve(reader.get_size());

			String name;
			Int2 layer;
			for (Size i = 0; i < reader.get_size(); i++)
			{
				// read the name
				if (!reader.read_name(i, name))
				{
					MINTY_ABORT(F("Failed to read Layer name at index {}.", i));
				}
				// read the layer data
				if (!reader.read(i, layer))
				{
					MINTY_ABORT(F("Failed to read Layer data at index {}.", i));
				}

				// add the layer collision
				builder.layerManagerBuilder.layerCollisions.add(
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
		reader.read("SavePaths", builder.assetManagerBuilder.savePaths);
		reader.read("Wraps", builder.assetManagerBuilder.wraps);

		reader.outdent();
	}
	if (reader.indent("Input"))
	{
		reader.outdent();
	}
	if (reader.indent("Render"))
	{
		reader.read("TargetFormat", builder.renderManagerBuilder.targetSurfaceFormat);

		reader.outdent();
	}
	if (reader.indent("Scene"))
	{
		reader.read("Initial", builder.sceneManagerBuilder.initialScene);

		reader.outdent();
	}

	return create(builder);
}

Owner<Context> Minty::Context::create(ContextBuilder const& builder)
{
	return Owner<Context>(builder);
}
