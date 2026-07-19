#pragma once

#include "Input/Mouse/MouseButton.hpp"
#include "Core/Data/BitArray.hpp"

namespace Minty
{
    struct MouseState
    {
        BitArray<static_cast<Size>(MouseButtonEnum::Count)> buttons;
        Float2 position;
        Float2 scroll;
    };
}