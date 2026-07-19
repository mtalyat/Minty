#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Vector.hpp"
#include "Input/Binding/AxisInputBinding.hpp"

namespace Minty
{
    class InputManager;

    class AxisInputAction
    {
#pragma region Method

    public:
        void update(InputManager const &inputManager);

#pragma endregion

#pragma region Variable

    private:
        Float m_current;
        Float m_previous;
        Vector<AxisInputBinding> m_bindings;

#pragma endregion
    };
}