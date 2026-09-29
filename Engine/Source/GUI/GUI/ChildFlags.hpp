#pragma once

namespace Minty
{
    enum class ChildFlagsEnum
    {
        None = 0,
        Borders = 1 << 0,
        AlwaysUseWindowPadding = 1 << 1,
        ResizeX = 1 << 2,
        ResizeY = 1 << 3,
        AutoResizeX = 1 << 4,
        AutoResizeY = 1 << 5,
        AlwaysAutoResize = 1 << 6,
        FrameStyle = 1 << 7,
        NavFlattened = 1 << 8,

        Count = 9,
        Default = None,
    };
}