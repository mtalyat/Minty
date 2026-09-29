#pragma once

namespace Minty
{
    enum class SliderFlagsEnum
    {
        None = 0,
        Logarithmic = 1 << 5,
        NoRoundToFormat = 1 << 6,
        NoInput = 1 << 7,
        WrapAround = 1 << 8,
        ClampOnInput = 1 << 9,
        ClampZeroRange = 1 << 10,
        NoSpeedTweaks = 1 << 11,
        ColorMarkers = 1 << 12,

        Count = 8,
        Default = None,
        
        AlwaysClamp = ClampOnInput|ClampZeroRange,
    };
}