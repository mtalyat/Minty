#pragma once

/**
 * @file WindowManager.h
 * @brief Header file defining the WindowManager class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Window/Type/Handle.hpp"
#include "Event/Type/EventCallback.hpp"
#include "Core/Type/UInt2.hpp"

namespace Minty
{
    struct WindowManagerInfo;
    struct WindowInfo;
    class Window;

    /**
     * @brief The WindowManager is responsible for managing windows in the application.
     */
    class WindowManager
    {
#pragma region Type

    private:
        struct Impl;

#pragma endregion

#pragma region Constructor

    public:
        WindowManager(WindowManagerInfo const &info);

        WindowManager(WindowManager const &) = delete;
        WindowManager(WindowManager &&) = delete;

        ~WindowManager();

#pragma endregion

#pragma region Operator

    public:
        WindowManager &operator=(WindowManager const &) = delete;
        WindowManager &operator=(WindowManager &&) = delete;

#pragma endregion

#pragma region Accessor

    public:
        WindowHandle get_main() const;

        Pointer get_native(WindowHandle const handle) const;

        UInt2 get_size(WindowHandle const handle) const;

        UInt2 get_framebuffer_size(WindowHandle const handle) const;

        Bool is_open(WindowHandle const handle) const;

        void set_event_callback(EventCallback const callback);

        static WindowManager &get_instance();

#pragma endregion

#pragma region Method

    public:
        WindowHandle create(WindowInfo const &info);

        void destroy(WindowHandle const handle);

        void maximize(WindowHandle const handle);

        void minimize(WindowHandle const handle);

        void restore(WindowHandle const handle);

        void close(WindowHandle const handle);

        void process_events();

        void sync();

#pragma endregion

#pragma region Variable

    private:
        Impl *mp_impl;

        static WindowManager *s_instance;

#pragma endregion
    };
}