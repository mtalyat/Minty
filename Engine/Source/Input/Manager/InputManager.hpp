#pragma once

#include "Input/Key/KeyboardState.hpp"
#include "Input/Gamepad/GamepadState.hpp"
#include "Input/Mouse/MouseState.hpp"

namespace Minty
{
    struct InputManagerInfo;

    class InputManager
    {
#pragma region Constructor

    public:
        InputManager(InputManagerInfo const &info);

#pragma endregion

#pragma region Method

    public:
        // Keyboard
        Bool get_key(KeyEnum const key) const;
        void set_key(KeyEnum const key, Bool const pressed);

        // Mouse
        Float2 get_mouse_position() const;
        void set_mouse_position(Float2 const position);
        Float2 get_mouse_scroll() const;
        void set_mouse_scroll(Float2 const scroll);
        Bool get_mouse_button(MouseButtonEnum const button) const;
        void set_mouse_button(MouseButtonEnum const button, Bool const pressed);

        // Gamepad
        Bool get_gamepad_button(GamepadButtonEnum const button) const;
        void set_gamepad_button(GamepadButtonEnum const button, Bool const pressed);
        Float get_gamepad_axis(GamepadAxisEnum const axis) const;
        void set_gamepad_axis(GamepadAxisEnum const axis, Float const value);

#pragma endregion

#pragma region Variable

    private:
        KeyboardState m_keyboardState;
        MouseState m_mouseState;
        GamepadState m_gamepadState;

#pragma endregion
    };
}