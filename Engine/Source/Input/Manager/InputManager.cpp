#include "pch.hpp"
#include "InputManager.hpp"

using namespace Minty;

InputManager* InputManager::sp_instance = nullptr;

Minty::InputManager::InputManager(InputManagerInfo const &info)
    : m_keyboardState(),
      m_mouseState(),
      m_gamepadStates()
{
    MINTY_ASSERT(sp_instance == nullptr, ErrorCodeEnum::Singleton_AlreadyExists);
    sp_instance = this;
}

Minty::InputManager::~InputManager()
{
    MINTY_ASSERT(sp_instance == this, ErrorCodeEnum::Singleton_DifferentObject);
    sp_instance = nullptr;
}

InputManager &Minty::InputManager::get_instance()
{
    MINTY_ASSERT(sp_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *sp_instance;
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

void Minty::InputManager::set_gamepad_connected(Int const gamepad, Bool const connected)
{
    m_gamepadStates.at(static_cast<Size>(gamepad)).connected = connected;
}

Bool Minty::InputManager::get_gamepad_connected(Int const gamepad) const
{
    return m_gamepadStates.at(static_cast<Size>(gamepad)).connected;
}

Bool Minty::InputManager::get_gamepad_button(Int const gamepad, GamepadButtonEnum const button) const
{
    return m_gamepadStates.at(static_cast<Size>(gamepad)).buttons.get(static_cast<Size>(button));
}

void Minty::InputManager::set_gamepad_button(Int const gamepad, GamepadButtonEnum const button, Bool const pressed)
{
    m_gamepadStates.at(static_cast<Size>(gamepad)).buttons.set(static_cast<Size>(button), pressed);
}

Float Minty::InputManager::get_gamepad_axis(Int const gamepad, GamepadAxisEnum const axis) const
{
    return m_gamepadStates.at(static_cast<Size>(gamepad)).axes.at(static_cast<Size>(axis));
}

void Minty::InputManager::set_gamepad_axis(Int const gamepad, GamepadAxisEnum const axis, Float const value)
{
    m_gamepadStates.at(static_cast<Size>(gamepad)).axes.at(static_cast<Size>(axis)) = value;
}
