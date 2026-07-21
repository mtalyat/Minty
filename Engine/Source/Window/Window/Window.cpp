#include "Window.hpp"

using namespace Minty;

#ifdef MINTY_WINDOWS
#include "Independence/Windows/Windows_Window.hpp"
#endif // MINTY_WINDOWS

Window* Minty::Window::s_main = nullptr;

Minty::Window::Window(WindowInfo const &info)
    : mp_impl(new Impl(info, this))
{
    // If no main window has been set, set this as the main window
    if (s_main == nullptr)
    {
        s_main = this;
    }
}

Minty::Window::~Window()
{
    // If this is the main window, clear it
    if (s_main == this)
    {
        s_main = nullptr;
    }

    delete mp_impl;
}

inline Pointer Minty::Window::get_native() const
{
    return mp_impl->get_native();
}

inline Int2 Minty::Window::get_size() const
{
    return mp_impl->get_size();
}

void Minty::Window::set_size(Int2 const size)
{
    mp_impl->set_size(size);
}

Int2 Minty::Window::get_position() const
{
    return mp_impl->get_position();
}

void Minty::Window::set_position(Int2 const position)
{
    mp_impl->set_position(position);
}

inline Int2 Minty::Window::get_framebuffer_size() const
{
    return mp_impl->get_framebuffer_size();
}

Bool Minty::Window::is_open() const
{
    return mp_impl->is_open();
}

Window &Minty::Window::get_main()
{
    MINTY_ASSERT(s_main != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_main;
}

void Minty::Window::set_main(Window *const window)
{
    s_main = window;
}
