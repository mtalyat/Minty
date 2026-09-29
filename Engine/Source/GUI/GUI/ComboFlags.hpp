#pragma once

namespace Minty
{
    enum class ComboFlagsEnum
    {
        None = 0,
        PopupAlignLeft = 1 << 0,
        HeightSmall = 1 << 1,
        HeightRegular = 1 << 2,
        HeightLarge = 1 << 3,
        HeightLargest = 1 << 4,
        NoArrowButton = 1 << 5,
        NoPreview = 1 << 6,
        WidthFitPreview = 1 << 7,

        Count = 8,
        Default = None,
    };
}