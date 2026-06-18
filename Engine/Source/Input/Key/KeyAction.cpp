#include "pch.h"
#include "KeyAction.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size GAMEPAD_ACTION_ENUM_COUNT = static_cast<Size>(KeyActionEnum::Count);
static constexpr Char const* MOUSE_ACTION_ENUM_STRINGS[GAMEPAD_ACTION_ENUM_COUNT] =
{
    "Up", // 0
    "Down", // 1
    "Hold", // 2
};

Bool Minty::Parser<KeyActionEnum>::parse(StringView const str, KeyActionEnum &value)
{
    return Tool::try_parse_enum(str, MOUSE_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT, value);
}

String Minty::Parser<KeyActionEnum>::to_string(KeyActionEnum const &obj)
{
    return Tool::to_string_enum(obj, MOUSE_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT);
}
