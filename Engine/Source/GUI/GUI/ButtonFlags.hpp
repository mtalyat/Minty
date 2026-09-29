#pragma once

namespace Minty
{
    enum class ButtonFlagsEnum
    {
        None = 0,
        MouseButtonLeft = 1 << 0,
        MouseButtonRight = 1 << 1,
        MouseButtonMiddle = 1 << 2,
        EnableNav = 1 << 3,
        AllowOverlap = 1 << 4,

        Count = 5,
        Default = None,
    };
}