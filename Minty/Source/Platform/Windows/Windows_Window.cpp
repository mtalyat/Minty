#include "pch.h"
#include "Windows_Window.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Format.h"
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
			MINTY_ASSERT(width >= 0, "Width is invalid.");
			MINTY_ASSERT(height >= 0, "Height is invalid.");
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in callback.");
			if (obj->m_eventCallback)
			{
				obj->m_eventCallback(WindowResizeEvent(static_cast<UInt>(width), static_cast<UInt>(height)));
			}
		});

	glfwSetWindowCloseCallback(mp_window, [](GLFWwindow* window)
		{
			Windows_Window* obj = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(obj, "Window is null in callback.");
			if (obj->m_eventCallback)
			{
				obj->m_eventCallback(WindowCloseEvent());
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
	glfwPollEvents();
}

void Minty::Windows_Window::sync()
{
	glfwWaitEvents();
}
