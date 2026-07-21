#pragma once

#include "Core/Data/Signal.hpp"
#include "Core/Type/UInt2.hpp"
#include "Input/Key/Key.hpp"
#include "Input/Key/KeyAction.hpp"
#include "Input/Key/KeyModifier.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "Input/Mouse/MouseAction.hpp"

namespace Minty
{
    struct WindowInfo;

    class Window
    {
#pragma region Type

    private:
        class Impl;

#pragma endregion

#pragma region Constructor

public:
        Window(WindowInfo const &info);
        ~Window();

        Window(Window const &) = delete;
        Window(Window &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        Window &operator=(Window const &) = delete;
        Window &operator=(Window &&) = delete;

#pragma endregion

#pragma region Accessor

    public:
        Pointer get_native() const;

        Int2 get_size() const;
        void set_size(Int2 const size);
        Int2 get_position() const;
        void set_position(Int2 const position);
        Int2 get_framebuffer_size() const;

        Bool is_open() const;

        static Window &get_main();
        static void set_main(Window *const window);

#pragma endregion

#pragma region Variable

    public:
        // Window events
        Signal<void(UInt2)> on_resize;
        Signal<void()> on_focus;
        Signal<void()> on_lost_focus;
        Signal<void()> on_minimize;
        Signal<void()> on_restore;
        Signal<void()> on_maximize;
        Signal<void()> on_close;
        Signal<void(KeyEnum, KeyActionEnum, KeyModifierFlagsEnum)> on_key;
        Signal<void(MouseButtonEnum, MouseActionEnum)> on_mouse_button;
        Signal<void(Float2)> on_mouse_move;
        Signal<void(Float2)> on_mouse_scroll;

    private:
        Impl *mp_impl;
        static Window *s_main;

#pragma endregion
    };
}