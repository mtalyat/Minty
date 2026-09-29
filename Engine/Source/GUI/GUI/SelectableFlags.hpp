#pragma once

namespace Minty
{
    enum class SelectableFlagsEnum
    {
        None = 0,
        NoAutoClosePopups = 1 << 0,
        SpanAllColumns = 1 << 1,
        AllowDoubleClick = 1 << 2,
        Disabled = 1 << 3,
        AllowOverlap = 1 << 4,
        Highlight = 1 << 5,
        SelectOnNav = 1 << 6,

        Count = 7,
        Default = None 
    };
}