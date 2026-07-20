#include "Window.hpp"

using namespace Minty;

#ifdef MINTY_WINDOWS
#include "Independence/Windows/Windows_Window.hpp"
#endif // MINTY_WINDOWS

Minty::Window::Window(WindowInfo const &info)
    : mp_impl(new Impl(info, this))
{
}

Minty::Window::~Window()
{
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
