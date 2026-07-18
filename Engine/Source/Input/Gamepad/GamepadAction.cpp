#include "pch.hpp"
#include "GamepadAction.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size GAMEPAD_ACTION_ENUM_COUNT = static_cast<Size>(GamepadActionEnum::Count);
static constexpr Char const* GAMEPAD_ACTION_ENUM_STRINGS[GAMEPAD_ACTION_ENUM_COUNT] =
{
    "Up", // 0
    "Down", // 1
};

Bool Minty::Parser<GamepadActionEnum>::parse(StringView const str, GamepadActionEnum &value)
{
    return Tool::try_parse_enum(str, GAMEPAD_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT, value);
}

String Minty::Parser<GamepadActionEnum>::to_string(GamepadActionEnum const &obj)
{
    return Tool::to_string_enum(obj, GAMEPAD_ACTION_ENUM_STRINGS, GAMEPAD_ACTION_ENUM_COUNT);
}
