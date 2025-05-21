#include "pch.h"
#include "Context.h"
#include "Minty/Component/_Component.h"
#include "Minty/System/_System.h"
#include "Minty/Event/_Event.h"

using namespace Minty;

Context* Context::s_instance = nullptr;

/// <summary>
/// Creates a new Context using the given ContextBuilder.
/// </summary>
/// <param name="builder">The input arguments.</param>
Minty::Context::Context(ContextBuilder const& builder)
	: mp_dualBuffer(nullptr)
	, m_memoryManager(nullptr)
	, m_jobManager(nullptr)
	, m_assetManager(nullptr)
	, m_inputManager(nullptr)
	, m_renderManager(nullptr)
	, m_sceneManager(nullptr)
	, m_managers()
	, m_window(nullptr)
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

	// create managers
	m_memoryManager = MemoryManager::create(builder.memoryManagerBuilder);
	m_jobManager = JobManager::create(builder.jobManagerBuilder);
	m_assetManager = AssetManager::create(builder.assetManagerBuilder);
	m_inputManager = InputManager::create(builder.inputManagerBuilder);
	m_renderManager = RenderManager::create(builder.renderManagerBuilder);
	m_sceneManager = SceneManager::create(builder.sceneManagerBuilder);
	m_managers.add(m_memoryManager.get());
	m_managers.add(m_jobManager.get());
	m_managers.add(m_renderManager.get());
	m_managers.add(m_assetManager.get());
	m_managers.add(m_inputManager.get());
	m_managers.add(m_sceneManager.get());

	// set the window event callback function
	m_window = m_renderManager->get_window();
	m_window->set_event_callback([this](Event& event) {
		handle_event(event);
		});

	// initialize managers
	initialize();
}

Minty::Context::~Context()
{
	// sync managers
	sync();

	// dispose managers
	dispose();

	// clean up
	delete mp_dualBuffer;
	m_memoryManager.release();
	m_jobManager.release();
	m_assetManager.release();
	m_renderManager.release();
	m_inputManager.release();
	m_sceneManager.release();
	m_managers.clear();
	m_window.release();

	s_instance = nullptr;
}

void Minty::Context::register_components()
{
	register_component<CameraComponent>("Camera");
	register_component<DirtyComponent>("Dirty");
	register_component<EnabledComponent>("Enabled");
	register_component<LayerComponent>("Layer");
	register_component<MeshComponent>("Mesh");
	register_component<NameComponent>("Name");
	register_component<RelationshipComponent>("Relationship");
	register_component<TransformComponent>("Transform");
	register_component<UUIDComponent>("UUID");
	register_component<VisibleComponent>("Visible");
}

void Minty::Context::register_systems()
{
	register_system<RenderSystem>("Render");
}

void Minty::Context::initialize()
{
	// initialize the managers
	for (Manager* manager : m_managers)
	{
		manager->initialize();
	}

	// register systems and components
	register_systems();
	register_components();
}

void Minty::Context::dispose()
{
	// dispose managers
	for (auto it = m_managers.rbegin(); it != m_managers.rend(); ++it)
	{
		(*it)->dispose();
	}
	m_managers.clear();

	// unregister systems
	m_registeredSystems.clear();
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
	// render managers
	for (Manager* manager : m_managers)
	{
		manager->render();
	}
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
	// send the event to specific managers, based on what the event is
	switch (event.get_type())
	{
	case EventType::WindowResize:
	{
		WindowResizeEvent& resizeEvent = static_cast<WindowResizeEvent&>(event);
		Debug::write_message("Window resized to ", resizeEvent.get_width(), "x", resizeEvent.get_height());
		break;
	}
	case EventType::WindowClose:
	{
		// TODO: handle event
		// if not canceled, close the window
		if (event.get_state() != EventState::Canceled)
		{
			Debug::write("Window closing...");
			m_window->close();
		}
		break;
	}
	case EventType::GamepadAxis:
		break;
	case EventType::GamepadButton:
		break;
	case EventType::GamepadConnected:
		break;
	case EventType::GamepadDisconnected:
		break;
	case EventType::Key:
	{
		KeyEvent& keyEvent = static_cast<KeyEvent&>(event);
		if (keyEvent.get_action() == KeyAction::Down)
		{
			Debug::write_message("Key down: ", to_string(keyEvent.get_key()));
		}
		else if (keyEvent.get_action() == KeyAction::Up)
		{
			Debug::write_message("Key up: ", to_string(keyEvent.get_key()));
		}
		else if (keyEvent.get_action() == KeyAction::Hold)
		{
			Debug::write_message("Key repeated: ", to_string(keyEvent.get_key()));
		}
		break;
	}
	case EventType::MouseButton:
	{
		MouseButtonEvent& mouseButtonEvent = static_cast<MouseButtonEvent&>(event);
		if (mouseButtonEvent.get_action() == KeyAction::Down)
		{
			Debug::write_message("Mouse button down: ", to_string(mouseButtonEvent.get_button()));
		}
		else if (mouseButtonEvent.get_action() == KeyAction::Up)
		{
			Debug::write_message("Mouse button up: ", to_string(mouseButtonEvent.get_button()));
		}
		else if (mouseButtonEvent.get_action() == KeyAction::Hold)
		{
			Debug::write_message("Mouse button repeated: ", to_string(mouseButtonEvent.get_button()));
		}
		break;
	}
	case EventType::MouseMoved:
		break;
	case EventType::MouseScrolled:
		break;
	default:
		MINTY_ABORT("Unhandled event type.");
		return;
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

Owner<Context> Minty::Context::create(ContextBuilder const& builder)
{
	return Owner<Context>(builder);
}
