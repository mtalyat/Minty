#pragma once

namespace Minty
{
    enum class ColorEditFlagsEnum
    {
        None = 0,
        NoAlpha = 1 << 1,
        NoPicker = 1 << 2,
        NoOptions = 1 << 3,
        NoSmallPreview = 1 << 4,
        NoInputs = 1 << 5,
        NoTooltip = 1 << 6,
        NoLabel = 1 << 7,
        NoSidePreview = 1 << 8,
        NoDragDrop = 1 << 9,
        NoBorder = 1 << 10,
        NoColorMarkers = 1 << 11,
        AlphaOpaque = 1 << 12,
        AlphaNoBg = 1 << 13,
        AlphaPreviewHalf = 1 << 14,
        AlphaBar = 1 << 18,
        HDR = 1 << 19,
        DisplayRGB = 1 << 20,
        DisplayHSV = 1 << 21,
        DisplayHex = 1 << 22,
        Uint8 = 1 << 23,
        Float = 1 << 24,
        PickerHueBar = 1 << 25,
        PickerHueWheel = 1 << 26,
        PickerNoRotate = 1 << 27,
        InputRGB = 1 << 28,
        InputHSV = 1 << 29,

        Count = 25,
        Default = None 
    };
}