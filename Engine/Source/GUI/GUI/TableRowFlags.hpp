#pragma once

namespace Minty
{
    enum class TableRowFlagsEnum
    {
        None = 0,
        Headers = 1 << 0,

        Count = 1,
        Default = None 
    };
}