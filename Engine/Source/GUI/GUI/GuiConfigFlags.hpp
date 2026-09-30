#pragma once

#include "Core/Tool/Enum.hpp"

namespace Minty
{
    enum class GuiConfigFlagsEnum
    {
        None = 0,
        NavEnableKeyboard = 1 << 0,
        NavEnableGamepad = 1 << 1,
        NoMouse = 1 << 4,
        NoMouseCursorChange = 1 << 5,
        NoKeyboard = 1 << 6,
        DockingEnable = 1 << 7,
        ViewportsEnable = 1 << 10,
        IsSRGB = 1 << 20,
        IsTouchScreen = 1 << 21,

        Count = 9,
        Default = None
    };
}