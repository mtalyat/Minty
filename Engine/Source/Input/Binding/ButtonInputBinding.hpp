#pragma once

#include "Input/Control/InputControl.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    class InputManager;

    struct ButtonInputBinding
    {
        InputControl control;

        Bool read(InputManager const &inputManager) const;
    };
}