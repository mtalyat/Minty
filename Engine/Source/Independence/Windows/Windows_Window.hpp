#pragma once

/**
 * @file Windows_Window.hpp
 * @brief Windows-specific implementation of the Window class, responsible for creating and managing a window on the Windows platform for rendering and user interaction.
 * @author Mitchell Talyat
 */

#include "Core/Type/Int2.hpp"
#include "Library/GLFW/GLFW.hpp"
#include "Window/Window/Window.hpp"

namespace Minty
{
    struct WindowInfo;

    class Window::Impl
    {
#pragma region Constructor

    public:
        Impl(WindowInfo const &info, Window* const owner);

        ~Impl();

        Impl(Impl const &) = delete;
        Impl(Impl &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        Impl &operator=(Impl const &) = delete;
        Impl &operator=(Impl &&) = delete;

#pragma endregion

#pragma region Accessor

    public:
        inline Pointer get_native() const { return mp_window; }

        Int2 get_size() const;
        void set_size(Int2 const size);
        Int2 get_position() const;
        void set_position(Int2 const position);
        Int2 get_framebuffer_size() const;

        Bool is_open() const;

#pragma endregion

#pragma region Method

    public:
        void maximize();

        void minimize();

        void restore();

        void close();

#pragma endregion

#pragma region Variable

    private:
        Window *mp_owner;
        GLFWwindow *mp_window;

#pragma endregion
    };
}
