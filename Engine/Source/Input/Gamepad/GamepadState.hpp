#pragma once

#include "Core/Data/BitArray.hpp"
#include "Core/Data/Array.hpp"
#include "Input/Gamepad/GamepadButton.hpp"
#include "Input/Gamepad/GamepadAxis.hpp"

namespace Minty
{
    struct GamepadState
    {
        BitArray<static_cast<Size>(GamepadButtonEnum::Count)> buttons;
        Array<Float, static_cast<Size>(GamepadAxisEnum::Count)> axes;
    };
}