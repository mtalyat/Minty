#include "pch.h"
#include "Window.h"
#include "Minty/Core/Macro.h"
#include "Platform/Windows/Windows_Window.h"

using namespace Minty;

Owner<Window> Minty::Window::create(WindowBuilder const& builder)
{
#ifdef MINTY_WINDOWS
    return Owner<Windows_Window>(builder);
#else
	MINTY_ABORT("Window creation is not supported on this platform.");
#endif // MINTY_WINDOWS
}

Minty::Window::Window(WindowBuilder const& builder)
	: m_id(builder.id)
	, m_position(builder.position)
	, m_size(builder.size)
	, m_title(builder.title)
	, m_eventCallback(builder.eventCallback)
{
}
