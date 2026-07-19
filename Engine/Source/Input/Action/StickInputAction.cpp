#include "pch.hpp"
#include "StickInputAction.hpp"

using namespace Minty;

void Minty::StickInputAction::update(InputManager const &inputManager)
{
    m_previous = m_current;
    m_current = Float2();

    Float2 value;
    for (StickInputBinding const &binding : m_bindings)
    {
        value = binding.read(inputManager);
        if (Math::abs(value.x) > Math::abs(m_current.x))
        {
            m_current.x = value.x;
        }
        if (Math::abs(value.y) > Math::abs(m_current.y))
        {
            m_current.y = value.y;
        }
    }
}