#pragma once

/**
 * @file WindowManager.h
 * @brief Header file defining the WindowManager class.
 * @author Mitchell Talyat
 */

#include "Windows_Window.h"
#include "Windows_GamepadData.h"
#include "Library/GLFW/GLFW.h"
#include "Platform/Type/Primitive.h"
#include "Window/Type/Handle.h"
#include "Core/Data/HandlePool.h"
#include "Core/Data/IndexPool.h"
#include "Event/Type/EventCallback.h"

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