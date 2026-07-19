#include "pch.hpp"
#include "AxisInputAction.hpp"
#include "Input/Manager/InputManager.hpp"
#include "Core/Math/Math.hpp"

using namespace Minty;

void Minty::AxisInputAction::update(InputManager const &inputManager)
{
    m_previous = m_current;
    m_current = 0.0f;
    
    Float value = 0.0f;
    for (AxisInputBinding const &binding : m_bindings)
    {
        value = binding.read(inputManager);
        if (Math::abs(value) > Math::abs(m_current))
        {
            m_current = value;
        }
    }
}