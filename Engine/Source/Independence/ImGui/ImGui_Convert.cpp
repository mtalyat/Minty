#include "ImGui_Convert.hpp"

using namespace Minty;

Key Converter<Key, ImGuiKey>::to_minty(ImGuiKey const value)
{
    MINTY_NOT_IMPLEMENTED();
    return Key();
}

ImGuiKey Converter<Key, ImGuiKey>::from_minty(Key const value)
{
    constexpr int MAPPING_OFFSET = 32;
    constexpr int MAPPING_SIZE = 96 - MAPPING_OFFSET + 1;
    static ImGuiKey const MAPPING[MAPPING_SIZE] = {
        ImGuiKey_Space, // 32,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_Apostrophe, // 39,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_Comma, // 44,
		ImGuiKey_Minus, // 45,
		ImGuiKey_Period, // 46,
		ImGuiKey_Slash, // 47,
		ImGuiKey_0, // 48,
		ImGuiKey_1, // 49,
		ImGuiKey_2, // 50,
		ImGuiKey_3, // 51,
		ImGuiKey_4, // 52,
		ImGuiKey_5, // 53,
		ImGuiKey_6, // 54,
		ImGuiKey_7, // 55,
		ImGuiKey_8, // 56,
		ImGuiKey_9, // 57,
        ImGuiKey_None,
		ImGuiKey_Semicolon, // 59,
        ImGuiKey_None,
		ImGuiKey_Equal, // 61,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_A, // 65,
		ImGuiKey_B, // 66,
		ImGuiKey_C, // 67,
		ImGuiKey_D, // 68,
		ImGuiKey_E, // 69,
		ImGuiKey_F, // 70,
		ImGuiKey_G, // 71,
		ImGuiKey_H, // 72,
		ImGuiKey_I, // 73,
		ImGuiKey_J, // 74,
		ImGuiKey_K, // 75,
		ImGuiKey_L, // 76,
		ImGuiKey_M, // 77,
		ImGuiKey_N, // 78,
		ImGuiKey_O, // 79,
		ImGuiKey_P, // 80,
		ImGuiKey_Q, // 81,
		ImGuiKey_R, // 82,
		ImGuiKey_S, // 83,
		ImGuiKey_T, // 84,
		ImGuiKey_U, // 85,
		ImGuiKey_V, // 86,
		ImGuiKey_W, // 87,
		ImGuiKey_X, // 88,
		ImGuiKey_Y, // 89,
		ImGuiKey_Z, // 90,
		ImGuiKey_LeftBracket, // 91,
		ImGuiKey_Backslash, // 92,
		ImGuiKey_RightBracket, // 93,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_GraveAccent, // 96,
    };
    constexpr int MAPPING_2_OFFSET = 256;
    constexpr int MAPPING_2_SIZE = 348 - MAPPING_2_OFFSET + 1;
    static ImGuiKey const MAPPING_2[MAPPING_2_SIZE] = {
		ImGuiKey_Escape, // 256,
		ImGuiKey_Enter, // 257,
		ImGuiKey_Tab, // 258,
		ImGuiKey_Backspace, // 259,
		ImGuiKey_Insert, // 260,
		ImGuiKey_Delete, // 261,
		ImGuiKey_RightArrow, // 262,
		ImGuiKey_LeftArrow, // 263,
		ImGuiKey_DownArrow, // 264,
		ImGuiKey_UpArrow, // 265,
		ImGuiKey_PageUp, // 266,
		ImGuiKey_PageDown, // 267,
		ImGuiKey_Home, // 268,
		ImGuiKey_End, // 269,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_CapsLock, // 280,
		ImGuiKey_ScrollLock, // 281,
		ImGuiKey_NumLock, // 282,
		ImGuiKey_PrintScreen, // 283,
		ImGuiKey_Pause, // 284,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_F1, // 290,
		ImGuiKey_F2, // 291,
		ImGuiKey_F3, // 292,
		ImGuiKey_F4, // 293,
		ImGuiKey_F5, // 294,
		ImGuiKey_F6, // 295,
		ImGuiKey_F7, // 296,
		ImGuiKey_F8, // 297,
		ImGuiKey_F9, // 298,
		ImGuiKey_F10, // 299,
		ImGuiKey_F11, // 300,
		ImGuiKey_F12, // 301,
		ImGuiKey_F13, // 302,
		ImGuiKey_F14, // 303,
		ImGuiKey_F15, // 304,
		ImGuiKey_F16, // 305,
		ImGuiKey_F17, // 306,
		ImGuiKey_F18, // 307,
		ImGuiKey_F19, // 308,
		ImGuiKey_F20, // 309,
		ImGuiKey_F21, // 310,
		ImGuiKey_F22, // 311,
		ImGuiKey_F23, // 312,
		ImGuiKey_F24, // 313,
		ImGuiKey_None, // 314, F25 unsupported
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_Keypad0, // 320,
		ImGuiKey_Keypad1, // 321,
		ImGuiKey_Keypad2, // 322,
		ImGuiKey_Keypad3, // 323,
		ImGuiKey_Keypad4, // 324,
		ImGuiKey_Keypad5, // 325,
		ImGuiKey_Keypad6, // 326,
		ImGuiKey_Keypad7, // 327,
		ImGuiKey_Keypad8, // 328,
		ImGuiKey_Keypad9, // 329,
		ImGuiKey_KeypadDecimal, // 330,
		ImGuiKey_KeypadDivide, // 331,
		ImGuiKey_KeypadMultiply, // 332,
		ImGuiKey_KeypadSubtract, // 333,
		ImGuiKey_KeypadAdd, // 334,
		ImGuiKey_KeypadEnter, // 335,
		ImGuiKey_KeypadEqual, // 336,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
		ImGuiKey_LeftShift, // 340,
		ImGuiKey_LeftCtrl, // 341,
		ImGuiKey_LeftAlt, // 342,
		ImGuiKey_LeftSuper, // 343,
		ImGuiKey_RightShift, // 344,
		ImGuiKey_RightCtrl, // 345,
		ImGuiKey_RightAlt, // 346,
		ImGuiKey_RightSuper, // 347,
		ImGuiKey_Menu, // 348,
    };

    Int keyValue = static_cast<Int>(value.value);

    // Key must be within the supported mapping ranges
    MINTY_ASSERT((keyValue >= MAPPING_OFFSET && keyValue < MAPPING_OFFSET + MAPPING_SIZE) ||
                 (keyValue >= MAPPING_2_OFFSET && keyValue < MAPPING_2_OFFSET + MAPPING_2_SIZE),
                ErrorCodeEnum::NotSupported);

    ImGuiKey result = keyValue >= MAPPING_2_OFFSET ? MAPPING_2[keyValue - MAPPING_2_OFFSET] : MAPPING[keyValue - MAPPING_OFFSET];

    // Key must be mapped to a valid ImGuiKey
    MINTY_ASSERT(result != ImGuiKey_None, ErrorCodeEnum::NotSupported);

    return result;
}

KeyModifier Converter<KeyModifier, ImGuiKey>::to_minty(ImGuiKey const value)
{
    MINTY_NOT_IMPLEMENTED();
    return KeyModifier();
}

ImGuiKey Converter<KeyModifier, ImGuiKey>::from_minty(KeyModifier const value)
{
    int mod = static_cast<int>(ImGuiMod_None);

    if (value.has_flag(KeyModifierFlagsEnum::Shift))
    {
        mod |= static_cast<int>(ImGuiMod_Shift);
    }
    if (value.has_flag(KeyModifierFlagsEnum::Control))
    {
        mod |= static_cast<int>(ImGuiMod_Ctrl);
    }
    if (value.has_flag(KeyModifierFlagsEnum::Alt))
    {
        mod |= static_cast<int>(ImGuiMod_Alt);
    }
    if (value.has_flag(KeyModifierFlagsEnum::Super))
    {
        mod |= static_cast<int>(ImGuiMod_Super);
    }
    MINTY_ASSERT(!value.has_flag(KeyModifierFlagsEnum::CapsLock), ErrorCodeEnum::NotSupported);
    MINTY_ASSERT(!value.has_flag(KeyModifierFlagsEnum::NumLock), ErrorCodeEnum::NotSupported);

    return static_cast<ImGuiKey>(mod);
}

MouseButtonEnum Converter<MouseButtonEnum, ImGuiMouseButton>::to_minty(ImGuiMouseButton const value)
{
    MINTY_NOT_IMPLEMENTED();
    return MouseButtonEnum();
}

ImGuiMouseButton Converter<MouseButtonEnum, ImGuiMouseButton>::from_minty(MouseButtonEnum const value)
{
    // Cannot be anything other than left, right and middle
    MINTY_ASSERT(value == MouseButtonEnum::Left || value == MouseButtonEnum::Right || value == MouseButtonEnum::Middle, ErrorCodeEnum::NotSupported);
    return static_cast<ImGuiMouseButton>(value);
}