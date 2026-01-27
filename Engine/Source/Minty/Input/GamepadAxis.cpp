#include "pch.h"
#include "GamepadAxis.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size GAMEPADAXIS_COUNT = 6;
static constexpr Char const* GAMEPADAXIS_STRINGS[GAMEPADAXIS_COUNT] =
{
	"LeftX",
	"LeftY",
	"RightX",
	"RightY",
	"LeftTrigger",
	"RightTrigger"
};

Bool Minty::Parser<GamepadAxis>::parse(StringView const str, GamepadAxis &value)
{
    return Tool::try_parse_enum(str, GAMEPADAXIS_STRINGS, GAMEPADAXIS_COUNT, value);
}

String Minty::Parser<GamepadAxis>::to_string(GamepadAxis const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), GAMEPADAXIS_STRINGS, GAMEPADAXIS_COUNT);
}