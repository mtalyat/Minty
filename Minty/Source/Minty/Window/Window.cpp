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
