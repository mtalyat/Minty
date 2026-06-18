#include "pch.h"
#include "MouseAction.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size GAMEPAD_ACTION_ENUM_COUNT = static_cast<Size>(MouseActionEnum::Count);
static constexpr Char const* GAMEPAD_ACTION_ENUM_STRINGS[GAMEPAD_ACTION_ENUM_COUNT] =
{
    "Up", // 0
    "Down", // 1
};

Bool Minty::Parser<MouseActionEnum>::parse(StringView const str, MouseActionEnum &value)
{
    return Tool::try_parse_enum(str, GAMEPAD_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT, value);
}

String Minty::Parser<MouseActionEnum>::to_string(MouseActionEnum const &obj)
{
    return Tool::to_string_enum(obj, GAMEPAD_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT);
}
