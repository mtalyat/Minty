#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Vector.hpp"
#include "Input/Binding/ButtonInputBinding.hpp"

namespace Minty
{
    class InputManager;

    class ButtonInputAction
    {
#pragma region Method

    public:
        void update(InputManager const &input_manager);

#pragma endregion

#pragma region Variable

    private:
        Bool m_current;
        Bool m_previous;
        Vector<ButtonInputBinding> m_bindings;

#pragma endregion
    };
}