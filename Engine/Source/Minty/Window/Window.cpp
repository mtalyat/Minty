#include "pch.h"
#include "Window.h"
#include "Minty/Core/Macro.h"
#include "Platform/Windows/Windows_Window.h"

using namespace Minty;

Owner<Window> Minty::Window::create(WindowInfo const &info)
{
#ifdef MINTY_WINDOWS
	return Owner<Windows_Window>(info);
#else
	MINTY_ABORT(ErrorCode::NotSupported);
#endif // MINTY_WINDOWS
}

Minty::Window::Window(WindowInfo const &info)
	: m_id(info.id), m_position(info.position), m_size(info.size), m_title(info.title), m_eventCallback(info.eventCallback)
{
}
