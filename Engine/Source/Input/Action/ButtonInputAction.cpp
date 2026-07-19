#include "pch.hpp"
#include "ButtonInputAction.hpp"
#include "Input/Manager/InputManager.hpp"

using namespace Minty;

void Minty::ButtonInputAction::update(InputManager const &inputManager)
{
    m_previous = m_current;
    m_current = false;

    for (ButtonInputBinding const &binding : m_bindings)
    {
        m_current |= binding.read(inputManager);
    }
}