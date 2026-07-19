#pragma once

#include "Input/Control/InputControl.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    class InputManager;

    struct AxisInputBinding
    {
        InputControl positive;
        InputControl negative;

        Float read(InputManager const &inputManager) const;
    };
}