#pragma once

#include "Input/Binding/InputBindingType.hpp"
#include "Input/Binding/StickInputBinding.hpp"
#include "Input/Binding/AxisInputBinding.hpp"
#include "Input/Binding/ButtonInputBinding.hpp"

namespace Minty
{
    struct InputBinding
    {
        InputBindingType type;

        union
        {
            ButtonInputBinding button;
            AxisInputBinding axis;
            StickInputBinding stick;
        };
    };
}