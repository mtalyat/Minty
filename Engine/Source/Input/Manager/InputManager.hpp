#pragma once

#include "Input/Key/KeyboardState.hpp"
#include "Input/Gamepad/GamepadState.hpp"
#include "Input/Mouse/MouseState.hpp"
#include "Input/Constant/Gamepad.hpp"
#include "Core/Data/Array.hpp"

namespace Minty
{
    struct InputManagerInfo;

    class InputManager
    {
#pragma region Constructor

    public:
        InputManager(InputManagerInfo const &info);
        ~InputManager();

        InputManager(InputManager const &) = delete;
        InputManager(InputManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        InputManager &operator=(InputManager const &) = delete;
        InputManager &operator=(InputManager &&) = delete;

        #pragma endregion

        #pragma region Accessor

        public:
        static InputManager& get_instance();

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
        void set_gamepad_connected(Int const gamepad, Bool const connected);
        Bool get_gamepad_connected(Int const gamepad) const;
        Bool get_gamepad_button(Int const gamepad, GamepadButtonEnum const button) const;
        void set_gamepad_button(Int const gamepad, GamepadButtonEnum const button, Bool const pressed);
        Float get_gamepad_axis(Int const gamepad, GamepadAxisEnum const axis) const;
        void set_gamepad_axis(Int const gamepad, GamepadAxisEnum const axis, Float const value);

#pragma endregion

#pragma region Variable

    private:
        KeyboardState m_keyboardState;
        MouseState m_mouseState;
        Array<GamepadState, MAX_GAMEPADS> m_gamepadStates;

        static InputManager* sp_instance;

#pragma endregion
    };
}