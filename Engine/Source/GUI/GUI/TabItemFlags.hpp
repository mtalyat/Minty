#pragma once

namespace Minty
{
    enum class TabItemFlagsEnum
    {
        None = 0,
        UnsavedDocument = 1 << 0,
        SetSelected = 1 << 1,
        NoCloseWithMiddleMouseButton = 1 << 2,
        NoPushId = 1 << 3,
        NoTooltip = 1 << 4,
        NoReorder = 1 << 5,
        Leading = 1 << 6,
        Trailing = 1 << 7,
        NoAssumedClosure = 1 << 8,

        Count = 9,
        Default = None 
    };
}