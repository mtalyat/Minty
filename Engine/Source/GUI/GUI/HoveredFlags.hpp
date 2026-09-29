#pragma once

namespace Minty
{
    enum class HoveredFlagsEnum
    {
        None = 0,
        ChildWindows = 1 << 0,
        RootWindow = 1 << 1,
        AnyWindow = 1 << 2,
        NoPopupHierarchy = 1 << 3,
        AllowWhenBlockedByPopup = 1 << 5,
        AllowWhenBlockedByActiveItem = 1 << 7,
        AllowWhenOverlappedByItem = 1 << 8,
        AllowWhenOverlappedByWindow = 1 << 9,
        AllowWhenDisabled = 1 << 10,
        NoNavOverride = 1 << 11,
        ForTooltip = 1 << 12,
        Stationary = 1 << 13,
        DelayNone = 1 << 14,
        DelayShort = 1 << 15,
        DelayNormal = 1 << 16,
        NoSharedDelay = 1 << 17,

        Count = 16,
        Default = None,

        AllowWhenOverlapped = AllowWhenOverlappedByItem|AllowWhenOverlappedByWindow,
        RectOnly = AllowWhenBlockedByPopup|AllowWhenBlockedByActiveItem|AllowWhenOverlapped,
        RootAndChildWindows = RootWindow|ChildWindows,
    };
}