#pragma once

namespace Minty
{
    enum class InputTextFlagsEnum
    {
        None = 0,
        CharsDecimal = 1 << 0,
        CharsHexadecimal = 1 << 1,
        CharsScientific = 1 << 2,
        CharsUppercase = 1 << 3,
        CharsNoBlank = 1 << 4,
        AllowTabInput = 1 << 5,
        EnterReturnsTrue = 1 << 6,
        EscapeClearsAll = 1 << 7,
        CtrlEnterForNewLine = 1 << 8,
        ReadOnly = 1 << 9,
        Password = 1 << 10,
        AlwaysOverwrite = 1 << 11,
        AutoSelectAll = 1 << 12,
        ParseEmptyRefVal = 1 << 13,
        DisplayEmptyRefVal = 1 << 14,
        NoHorizontalScroll = 1 << 15,
        NoUndoRedo = 1 << 16,
        ElideLeft = 1 << 17,
        CallbackCompletion = 1 << 18,
        CallbackHistory = 1 << 19,
        CallbackAlways = 1 << 20,
        CallbackCharFilter = 1 << 21,
        CallbackResize = 1 << 22,
        CallbackEdit = 1 << 23,
        WordWrap = 1 << 24,

        Count = 25,
        Default = None 
    };
}