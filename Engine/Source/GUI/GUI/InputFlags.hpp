#pragma once

namespace Minty
{
    enum class InputFlagsEnum
    {
        None = 0,
        Repeat = 1 << 0,
        RouteActive = 1 << 10,
        RouteFocused = 1 << 11,
        RouteGlobal = 1 << 12,
        RouteAlways = 1 << 13,
        RouteOverFocused = 1 << 14,
        RouteOverActive = 1 << 15,
        RouteUnlessBgFocused = 1 << 16,
        RouteFromRootWindow = 1 << 17,
        Tooltip = 1 << 18,

        Count = 10,
        Default = None 
    };
}