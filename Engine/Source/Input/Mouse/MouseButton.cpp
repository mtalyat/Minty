#include "pch.hpp"
#include "MouseButton.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size MOUSE_BUTTON_ENUM_COUNT = static_cast<Size>(MouseButtonEnum::Count);
static constexpr Char const* MOUSE_BUTTON_ENUM_STRINGS[MOUSE_BUTTON_ENUM_COUNT] =
{
    "Button1", // 0
    "Button2", // 1
    "Button3", // 2
    "Button4", // 3
    "Button5", // 4
    "Button6", // 5
    "Button7", // 6
    "Button8", // 7
};
static constexpr Char const* MOUSE_BUTTON_ENUM_STRINGS_ALIASES[MOUSE_BUTTON_ENUM_COUNT] =
{
    "Left", // 0
    "Right", // 1
    "Middle", // 2
    "X1", // 3
    "X2", // 4
    "", // 5
    "", // 6
    "", // 7
};

Bool Minty::Parser<MouseButtonEnum>::parse(StringView const str, MouseButtonEnum &value)
{
    return Tool::try_parse_enum(str, MOUSE_BUTTON_ENUM_STRINGS, MOUSE_BUTTON_ENUM_COUNT, value) ||
           Tool::try_parse_enum(str, MOUSE_BUTTON_ENUM_STRINGS_ALIASES, MOUSE_BUTTON_ENUM_COUNT, value);
}

String Minty::Parser<MouseButtonEnum>::to_string(MouseButtonEnum const &obj)
{
    String result = Tool::to_string_enum(obj, MOUSE_BUTTON_ENUM_STRINGS, MOUSE_BUTTON_ENUM_COUNT);
    if (result.is_empty())
    {
        result = Tool::to_string_enum(obj, MOUSE_BUTTON_ENUM_STRINGS_ALIASES, MOUSE_BUTTON_ENUM_COUNT);
    }
    return result;
}
