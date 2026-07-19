#pragma once

#include "Input/Key/Key.hpp"
#include "Core/Data/BitArray.hpp"

namespace Minty
{
    struct KeyboardState
    {
        BitArray<static_cast<Size>(KeyEnum::Count)> keys;
    };
}