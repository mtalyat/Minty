#include "Windows_WindowManager.hpp"
#include "Core/Debug/DebugF.hpp"
#include "Event/Type/EventCallback.hpp"
#include "Window/Window/WindowInfo.hpp"
#include "Window/Manager/WindowManagerInfo.hpp"

#include "Event/Keyboard/__Keyboard.hpp"
#include "Event/Mouse/__Mouse.hpp"
#include "Event/Window/__Window.hpp"
#include "Event/Gamepad/__Gamepad.hpp"
#include "Input/Constant/__Constant.hpp"

using namespace Minty;

struct Windows_CallbackData
{
    Windows_WindowManager* p_manager;
    WindowHandle handle;
};

static void error_callback(int error_code, const char* description)
{
    MINTY_LOG_ERROR_F("GLFW Error {}: {}", error_code, description);
}

static void save_restore_data(Windows_WindowData& windowData)
{
    // Get current position and size
    glfwGetWindowPos(windowData.p_window, &windowData.restorePosition.x, &windowData.restorePosition.y);
    glfwGetWindowSize(windowData.p_window, &windowData.restoreSize.x, &windowData.restoreSize.y);
}

Minty::Windows_WindowManager::Windows_WindowManager(WindowManagerInfo const &info)
    : m_windows(),
      m_gamepads(),
      m_eventCallback(info.eventCallback)
{
    // Initialize GLFW
    if(!glfwInit())
    {
        MINTY_ABORT(ErrorCodeEnum::Library_InitializationFailed);
    }
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Initialize gamepad data
    m_gamepads.resize(GLFW_JOYSTICK_LAST + 1);
}

Minty::Windows_WindowManager::~Windows_WindowManager()
{
    // Sync before destroying windows to process any pending events
    sync();

    // Destroy all windows
    for (WindowHandle handle : m_windows.get_handles())
    {
        destroy(handle);
    }

    // Deinitialize GLFW
    glfwTerminate();
}

Pointer Minty::Windows_WindowManager::get_native(WindowHandle const handle) const
{
    Windows_WindowData const& windowData = m_windows.at(handle);
    return static_cast<Pointer>(windowData.p_window);
}

UInt2 Minty::Windows_WindowManager::get_size(WindowHandle const handle) const
{
    Windows_WindowData const& windowData = m_windows.at(handle);
    Int width, height;
    glfwGetWindowSize(windowData.p_window, &width, &height);
    return UInt2(static_cast<UInt>(width), static_cast<UInt>(height));
}

UInt2 Minty::Windows_WindowManager::get_framebuffer_size(WindowHandle const handle) const
{
    Windows_WindowData const& windowData = m_windows.at(handle);
    Int width, height;
    glfwGetFramebufferSize(windowData.p_window, &width, &height);
    return UInt2(static_cast<UInt>(width), static_cast<UInt>(height));
}

Bool Minty::Windows_WindowManager::is_open(WindowHandle const handle) const
{
    Windows_WindowData const& windowData = m_windows.at(handle);
    return !glfwWindowShouldClose(windowData.p_window);
}

WindowHandle Minty::Windows_WindowManager::create(WindowInfo const &info)
{
    // Create window data
    WindowHandle const handle = m_windows.add(Windows_WindowData{});
    Windows_WindowData &windowData = m_windows.at(handle);
    windowData.restorePosition = info.position;
    windowData.restoreSize = info.size;

    // Create the GLFW window
    windowData.p_window = glfwCreateWindow(
        static_cast<Int>(info.size.x), 
        static_cast<Int>(info.size.y), 
        info.title.get_data(), 
        nullptr, // Monitor
        nullptr);// Share
    MINTY_ASSERT(windowData.p_window, ErrorCodeEnum::Window_CreationFailed);

    // Set user pointer for callback functions
    Windows_CallbackData* callbackData = new Windows_CallbackData();
    callbackData->p_manager = this;
    callbackData->handle = handle;
    glfwSetWindowUserPointer(windowData.p_window, callbackData);

    // Set window values
    glfwSetWindowTitle(windowData.p_window, info.title.get_data());
    glfwSetWindowPos(windowData.p_window, info.position.x, info.position.y);
    glfwSetWindowSize(windowData.p_window, info.size.x, info.size.y);

    // Set callbacks
    glfwSetWindowSizeCallback(windowData.p_window, [](GLFWwindow* window, Int width, Int height)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                WindowResizeEvent event(static_cast<UInt>(width), static_cast<UInt>(height));
                manager->m_eventCallback(event);
            }
		});

	glfwSetWindowCloseCallback(windowData.p_window, [](GLFWwindow* window)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
			Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                WindowCloseEvent event{};
                manager->m_eventCallback(event);
            }
		});

	glfwSetKeyCallback(windowData.p_window, [](GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
			Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                KeyEvent event(static_cast<KeyEnum>(key), static_cast<KeyActionEnum>(action), static_cast<KeyModifierFlagsEnum>(mods));
                manager->m_eventCallback(event);
            }
		});

	glfwSetMouseButtonCallback(windowData.p_window, [](GLFWwindow* window, Int button, Int action, Int mods)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
			Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                MouseButtonEvent event(static_cast<MouseButtonEnum>(button), static_cast<KeyActionEnum>(action), static_cast<KeyModifierFlagsEnum>(mods));
                manager->m_eventCallback(event);
            }
		});

	glfwSetCursorPosCallback(windowData.p_window, [](GLFWwindow* window, WFloat x, WFloat y)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
			Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                MouseMoveEvent event(Float2(static_cast<Float>(x), static_cast<Float>(y)));
                manager->m_eventCallback(event);
			}
		});

	glfwSetScrollCallback(windowData.p_window, [](GLFWwindow* window, WFloat xOffset, WFloat yOffset)
		{
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
			Windows_WindowManager* manager = callbackData->p_manager;
			if (manager && manager->m_eventCallback)
            {
                MouseScrollEvent event(Float2(static_cast<Float>(xOffset), static_cast<Float>(yOffset)));
                manager->m_eventCallback(event);
            }
		});

    // TODO: set icon

	// If no main window, set that to this one
	if (m_mainWindow == INVALID_HANDLE)
	{
		m_mainWindow = handle;
	}

    // Return handle, since window was added to pool above
    return handle;
}

void Minty::Windows_WindowManager::destroy(WindowHandle const handle)
{
	// If this was the main window, unset it and select another one if available
	if (handle == m_mainWindow)
	{
		m_mainWindow = INVALID_HANDLE;
		if (!m_windows.is_empty())
		{
			// TODO: find cheaper way to get a handle without having to get the whole list of handles
			m_mainWindow = m_windows.get_handles().front();
		}
	}

    // Destroy Window
    Windows_WindowData const &windowData = m_windows.at(handle);
    glfwDestroyWindow(windowData.p_window);

    // Remove from pool
    m_windows.remove(handle);
}

void Minty::Windows_WindowManager::maximize(WindowHandle const handle)
{
    Windows_WindowData& windowData = m_windows.at(handle);
    save_restore_data(windowData);
    glfwMaximizeWindow(windowData.p_window);
}

void Minty::Windows_WindowManager::minimize(WindowHandle const handle)
{
    Windows_WindowData& windowData = m_windows.at(handle);
    save_restore_data(windowData);
    glfwIconifyWindow(windowData.p_window);
}

void Minty::Windows_WindowManager::restore(WindowHandle const handle)
{
    Windows_WindowData& windowData = m_windows.at(handle);
    glfwSetWindowPos(windowData.p_window, windowData.restorePosition.x, windowData.restorePosition.y);
    glfwSetWindowSize(windowData.p_window, windowData.restoreSize.x, windowData.restoreSize.y);
}

void Minty::Windows_WindowManager::close(WindowHandle const handle)
{
    Windows_WindowData& windowData = m_windows.at(handle);
    glfwSetWindowShouldClose(windowData.p_window, GLFW_TRUE);
}

void Minty::Windows_WindowManager::process_events()
{
    // process GLFW events
    glfwPollEvents();

    // process gamepad events
    // check for each controller
	GLFWgamepadstate state;
	for (Index i = 0; i <= GLFW_JOYSTICK_LAST; i++)
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
				m_gamepads.insert(i, data);
			}

			// get data
			GamepadData& data = m_gamepads.at(i);
			GLFWgamepadstate& oldState = data.state;

			// check button changes
			for (Int j = 0; j <= GLFW_GAMEPAD_BUTTON_LAST; j++)
			{
				if (state.buttons[j] != oldState.buttons[j])
				{
					GamepadButtonEvent event(i, static_cast<GamepadButtonEnum>(j), static_cast<GamepadActionEnum>(state.buttons[j]));
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
					GamepadAxisEvent event(i, static_cast<GamepadAxisEnum>(j), state.axes[j]);
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

void Minty::Windows_WindowManager::sync()
{
    glfwWaitEvents();
}
