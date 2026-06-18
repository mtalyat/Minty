#include "pch.h"
#include "WindowManager.h"
#include "Core/Debug/Debug.h"

using namespace Minty;

#ifdef MINTY_WINDOWS
#include "Independence/Windows/Windows_WindowManager.h"
struct WindowManager::Impl
{
    Windows_WindowManager windowManager;
};
#else
#error "No window manager implementation defined for the current platform."
#endif // MINTY_WINDOWS

WindowManager* WindowManager::s_instance = nullptr;

Minty::WindowManager::WindowManager(WindowManagerInfo const &info)
    : mp_impl(nullptr)
{
    mp_impl = new Impl(info);

    MINTY_ASSERT(s_instance == nullptr, ErrorCodeEnum::Singleton_AlreadyExists);
    s_instance = this;
}

Minty::WindowManager::~WindowManager()
{
    delete mp_impl;

    MINTY_ASSERT(s_instance == this, ErrorCodeEnum::Singleton_DifferentObject);
    s_instance = nullptr;
}

WindowHandle Minty::WindowManager::get_main() const
{
    return mp_impl->windowManager.get_main();
}

Pointer Minty::WindowManager::get_native(WindowHandle const handle) const
{
    return mp_impl->windowManager.get_native(handle);
}

UInt2 Minty::WindowManager::get_size(WindowHandle const handle) const
{
    return mp_impl->windowManager.get_size(handle);
}

UInt2 Minty::WindowManager::get_framebuffer_size(WindowHandle const handle) const
{
    return mp_impl->windowManager.get_framebuffer_size(handle);
}

Bool Minty::WindowManager::is_open(WindowHandle const handle) const
{
    return mp_impl->windowManager.is_open(handle);
}

void Minty::WindowManager::set_event_callback(EventCallback const callback)
{
    mp_impl->windowManager.set_event_callback(callback);
}

WindowManager &Minty::WindowManager::get_instance()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_instance;
}

WindowHandle Minty::WindowManager::create(WindowInfo const &info)
{
    return mp_impl->windowManager.create(info);
}

void Minty::WindowManager::destroy(WindowHandle const handle)
{
    mp_impl->windowManager.destroy(handle);
}

void Minty::WindowManager::maximize(WindowHandle const handle)
{
    mp_impl->windowManager.maximize(handle);
}

void Minty::WindowManager::minimize(WindowHandle const handle)
{
    mp_impl->windowManager.minimize(handle);
}

void Minty::WindowManager::restore(WindowHandle const handle)
{
    mp_impl->windowManager.restore(handle);
}

void Minty::WindowManager::close(WindowHandle const handle)
{
    mp_impl->windowManager.close(handle);
}

void Minty::WindowManager::process_events()
{
    mp_impl->windowManager.process_events();
}

void Minty::WindowManager::sync()
{
    mp_impl->windowManager.sync();
}
