#include "pch.h"
#include "Windows_Window.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Format.h"
#include "Minty/Event/_Event.h"
#include "Minty/Library/STB.h"

using namespace Minty;

Int Windows_Window::s_windowCount = 0;

static void error_callback(Int error, Char const* description)
{
	MINTY_ERROR(F("GLFW error ({}): {}", error, description).get_data());
}

Minty::Windows_Window::Windows_Window(WindowBuilder const& builder)
	: Window(builder)
	, mp_window(nullptr)
	, m_gamepads()
	, m_restorePosition(builder.position)
	, m_restoreSize(builder.size)
{
	// initialize GLFW if first window
	if (!s_windowCount)
	{
		if (!glfwInit())
		{
			MINTY_ABORT("Failed to initialize_swapchain GLFW.");
		}

		glfwSetErrorCallback(error_callback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}
	s_windowCount++;

	mp_window = glfwCreateWindow(static_cast<Int>(builder.size.x), static_cast<Int>(builder.size.y), "", nullptr, nullptr);

	MINTY_ASSERT(mp_window, "Failed to create window.");

	glfwSetWindowUserPointer(mp_window, this);

	restore();

	// set callbacks

	glfwSetWindowSizeCallback(mp_window, [](GLFWwindow* window, Int width, Int height)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Window Size callback.");
			if (obj->m_eventCallback)
			{
				WindowResizeEvent event(static_cast<UInt>(width), static_cast<UInt>(height));
				obj->m_eventCallback(event);
			}
		});

	glfwSetWindowCloseCallback(mp_window, [](GLFWwindow* window)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Window Close callback.");
			if (obj->m_eventCallback)
			{
				WindowCloseEvent event{};
				obj->m_eventCallback(event);
			}
		});

	glfwSetKeyCallback(mp_window, [](GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Key callback.");
			if (obj->m_eventCallback)
			{
				KeyEvent event(static_cast<Key>(key), static_cast<KeyAction>(action), static_cast<KeyModifiers>(mods));
				obj->m_eventCallback(event);
			}
		});

	glfwSetMouseButtonCallback(mp_window, [](GLFWwindow* window, Int button, Int action, Int mods)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Mouse Button callback.");
			if (obj->m_eventCallback)
			{
				MouseButtonEvent event(static_cast<MouseButton>(button), static_cast<KeyAction>(action), static_cast<KeyModifiers>(mods));
				obj->m_eventCallback(event);
			}
		});

	glfwSetCursorPosCallback(mp_window, [](GLFWwindow* window, Double x, Double y)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Mouse Move callback.");
			if (obj->m_eventCallback)
			{
				MouseMoveEvent event(Float2(static_cast<Float>(x), static_cast<Float>(y)));
				obj->m_eventCallback(event);
			}
		});

	glfwSetScrollCallback(mp_window, [](GLFWwindow* window, Double xOffset, Double yOffset)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in Mouse Scroll callback.");
			if (obj->m_eventCallback)
			{
				MouseScrollEvent event(Float2(static_cast<Float>(xOffset), static_cast<Float>(yOffset)));
				obj->m_eventCallback(event);
			}
		});
}

Minty::Windows_Window::~Windows_Window()
{
	glfwDestroyWindow(mp_window);

	s_windowCount--;

	// terminate GLFW if no more windows
	if (!s_windowCount)
	{
		glfwTerminate();
	}
}

void Minty::Windows_Window::set_title(String const& title)
{
	Window::set_title(title);
	glfwSetWindowTitle(mp_window, title.get_data());
}

void Minty::Windows_Window::set_position(Int2 const& position)
{
	Window::set_position(position);
	glfwSetWindowPos(mp_window, position.x, position.y);
}

void Minty::Windows_Window::set_size(UInt2 const& size)
{
	Window::set_size(size);
	glfwSetWindowSize(mp_window, size.x, size.y);
}

UInt2 Minty::Windows_Window::get_framebuffer_size() const
{
	Int2 size;
	glfwGetFramebufferSize(mp_window, &size.x, &size.y);
	MINTY_ASSERT(size.x >= 0, "Width is invalid.");
	MINTY_ASSERT(size.y >= 0, "Height is invalid.");
	return UInt2(static_cast<UInt>(size.x), static_cast<UInt>(size.y));
}

CursorMode Minty::Windows_Window::get_cursor_mode() const
{
	switch (glfwGetInputMode(mp_window, GLFW_CURSOR))
	{
	case GLFW_CURSOR_NORMAL:
		return CursorMode::Normal;
	case GLFW_CURSOR_HIDDEN:
		return CursorMode::Hidden;
	case GLFW_CURSOR_DISABLED:
		return CursorMode::Disabled;
	default:
		return CursorMode();
	}
}

void Minty::Windows_Window::set_cursor_mode(CursorMode const mode)
{
	switch (mode)
	{
	case CursorMode::Normal:
		glfwSetInputMode(mp_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case CursorMode::Hidden:
		glfwSetInputMode(mp_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case CursorMode::Disabled:
		glfwSetInputMode(mp_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	default:
		MINTY_ABORT("Invalid CursorMode.");
		break;
	}
}

void* Minty::Windows_Window::get_native() const
{
	return mp_window;
}

void Minty::Windows_Window::save_restore_info()
{
	glfwGetWindowPos(mp_window, &m_restorePosition.x, &m_restorePosition.y);
	glfwGetWindowSize(mp_window, &m_restoreSize.x, &m_restoreSize.y);
}

void Minty::Windows_Window::process_window_events()
{
	glfwPollEvents();
}

void Minty::Windows_Window::process_gamepad_events()
{
	GLFWgamepadstate state;

	// check for each controller
	for (Int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwGetGamepadState(i, &state))
		{
			if (!m_gamepads.contains(i))
			{
				// newly connected controller

				// create gamepad data
				GamepadData data{};
				data.state = GLFWgamepadstate{};
				data.name = glfwGetGamepadName(i);

				// trigger event
				GamepadConnectEvent event(i);
				if (m_eventCallback)
				{
					m_eventCallback(event);
				}

				// add to map
				m_gamepads.add(i, data);
			}

			// get data
			GamepadData& data = m_gamepads.at(i);
			GLFWgamepadstate& oldState = data.state;

			// check button changes
			for (Int j = 0; j <= GLFW_GAMEPAD_BUTTON_LAST; j++)
			{
				if (state.buttons[j] != oldState.buttons[j])
				{
					GamepadButtonEvent event(i, static_cast<GamepadButton>(j), static_cast<KeyAction>(state.buttons[j]));
					if (m_eventCallback)
					{
						m_eventCallback(event);
					}
				}
			}

			// check axis changes
			for (Int j = 0; j <= GLFW_GAMEPAD_AXIS_LAST; j++)
			{
				// round to zero if a stick
				if (j <= GLFW_GAMEPAD_AXIS_RIGHT_Y && Math::abs(state.axes[j]) < JOYSTICK_DEADZONE)
				{
					state.axes[j] = 0.0f;
				}

				// compare to old value
				if (state.axes[j] != oldState.axes[j])
				{
					// value changed, trigger callback
					GamepadAxisEvent event(i, static_cast<GamepadAxis>(j), state.axes[j]);
					if (m_eventCallback)
					{
						m_eventCallback(event);
					}
				}
			}

			// copy over new state data
			memcpy(&oldState, &state, sizeof(GLFWgamepadstate));
		}
		else if (m_gamepads.contains(i))
		{
			// controller disconnected
			
			// trigger event
			GamepadDisconnectEvent event(i);
			if (m_eventCallback)
			{
				m_eventCallback(event);
			}

			// remove from map
			m_gamepads.remove(i);
		}
	}
}

void Minty::Windows_Window::maximize()
{
	save_restore_info();
	glfwMaximizeWindow(mp_window);
}

void Minty::Windows_Window::minimize()
{
	save_restore_info();
	glfwIconifyWindow(mp_window);
}

void Minty::Windows_Window::restore()
{
	glfwSetWindowPos(mp_window, m_restorePosition.x, m_restorePosition.y);
	glfwSetWindowSize(mp_window, m_restoreSize.x, m_restoreSize.y);
}

void Minty::Windows_Window::close()
{
	glfwSetWindowShouldClose(mp_window, GLFW_TRUE);
}

Bool Minty::Windows_Window::is_open() const
{
	return !glfwWindowShouldClose(mp_window);
}

void Minty::Windows_Window::process_events()
{
	process_window_events();
	process_gamepad_events();
}

void Minty::Windows_Window::sync()
{
	glfwWaitEvents();
}
