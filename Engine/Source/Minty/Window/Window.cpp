#include "pch.h"
#include "Window.h"
#include "Minty/Core/Macro.h"
#include "Minty/Window/WindowInfo.h"
#ifdef MINTY_WINDOWS
#include "Platform/Windows/Windows_Window.h"
#endif // MINTY_WINDOWS

using namespace Minty;

Minty::Window::Window(WindowInfo const &info)
	: m_position(info.position), m_size(info.size), m_title(info.title), m_eventCallback(info.eventCallback), m_id(info.id)
{
}

Unique<Window> Minty::Window::create(WindowInfo const &info)
{
#ifdef MINTY_WINDOWS
	return Unique<Windows_Window>::create(info);
#else
	MINTY_NOT_IMPLEMENTED();
	return nullptr;
#endif // MINTY_WINDOWS
}
