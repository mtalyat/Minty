#pragma once

#include "Input/Control/InputControl.hpp"
#include "Core/Type/Float2.hpp"

namespace Minty
{
    class InputManager;

    struct StickInputBinding
    {
        InputControl up;
        InputControl down;
        InputControl left;
        InputControl right;

        Float2 read(InputManager const &inputManager) const;
    };
}