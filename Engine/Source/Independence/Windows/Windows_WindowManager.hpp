#pragma once

/**
 * @file WindowManager.h
 * @brief Header file defining the WindowManager class.
 * @author Mitchell Talyat
 */

#include "Windows_Window.hpp"
#include "Windows_GamepadData.hpp"
#include "Library/GLFW/GLFW.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Window/Type/Handle.hpp"
#include "Core/Data/HandlePool.hpp"
#include "Core/Data/IndexPool.hpp"
#include "Event/Type/EventCallback.hpp"

namespace Minty
{
    struct WindowManagerInfo;
    struct WindowInfo;

    class Windows_WindowManager
    {
#pragma region Constructor

    public:
        Windows_WindowManager(WindowManagerInfo const &info);

        ~Windows_WindowManager();

#pragma endregion

#pragma region Accessor

    public:
        WindowHandle get_main() const { return m_mainWindow; }

        Pointer get_native(WindowHandle const handle) const;

        UInt2 get_size(WindowHandle const handle) const;

        UInt2 get_framebuffer_size(WindowHandle const handle) const;

        Bool is_open(WindowHandle const handle) const;

        inline void set_event_callback(EventCallback const callback) { m_eventCallback = callback; }

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
        WindowHandle m_mainWindow;
        HandlePool<Windows_WindowData, Window> m_windows;
        EventCallback m_eventCallback;
        IndexPool<GamepadData> m_gamepads;

#pragma endregion
    };
}