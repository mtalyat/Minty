#include "pch.hpp"
#include "InputManager.hpp"

using namespace Minty;

Minty::InputManager::InputManager(InputManagerInfo const &info)
    : m_keyboardState(),
      m_mouseState(),
      m_gamepadState()
{
}

Bool Minty::InputManager::get_key(KeyEnum const key) const
{
    return m_keyboardState.keys.get(static_cast<Size>(key));
}

void Minty::InputManager::set_key(KeyEnum const key, Bool const pressed)
{
    m_keyboardState.keys.set(static_cast<Size>(key), pressed);
}

Float2 Minty::InputManager::get_mouse_position() const
{
    return m_mouseState.position;
}

void Minty::InputManager::set_mouse_position(Float2 const position)
{
    m_mouseState.position = position;
}

Float2 Minty::InputManager::get_mouse_scroll() const
{
    return m_mouseState.scroll;
}

void Minty::InputManager::set_mouse_scroll(Float2 const scroll)
{
    m_mouseState.scroll = scroll;
}

Bool Minty::InputManager::get_mouse_button(MouseButtonEnum const button) const
{
    return m_mouseState.buttons.get(static_cast<Size>(button));
}

void Minty::InputManager::set_mouse_button(MouseButtonEnum const button, Bool const pressed)
{
    m_mouseState.buttons.set(static_cast<Size>(button), pressed);
}

Bool Minty::InputManager::get_gamepad_button(GamepadButtonEnum const button) const
{
    return m_gamepadState.buttons.get(static_cast<Size>(button));
}

void Minty::InputManager::set_gamepad_button(GamepadButtonEnum const button, Bool const pressed)
{
    m_gamepadState.buttons.set(static_cast<Size>(button), pressed);
}

Float Minty::InputManager::get_gamepad_axis(GamepadAxisEnum const axis) const
{
    return m_gamepadState.axes.at(static_cast<Size>(axis));
}

void Minty::InputManager::set_gamepad_axis(GamepadAxisEnum const axis, Float const value)
{
    m_gamepadState.axes.at(static_cast<Size>(axis)) = value;
}
