#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Vector.hpp"
#include "Input/Binding/StickInputBinding.hpp"

namespace Minty
{
    class InputManager;

    class StickInputAction
    {
#pragma region Method

    public:
        void update(InputManager const &inputManager);

#pragma endregion

#pragma region Variable

    private:
        Float2 m_current;
        Float2 m_previous;
        Vector<StickInputBinding> m_bindings;

#pragma endregion
    };
}