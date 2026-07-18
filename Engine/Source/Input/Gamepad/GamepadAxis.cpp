#include "pch.hpp"
#include "GamepadAxis.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size GAMEPADAXIS_COUNT = static_cast<Size>(GamepadAxisEnum::Count);
static constexpr Char const* GAMEPADAXIS_STRINGS[GAMEPADAXIS_COUNT] =
{
	"LeftX",
	"LeftY",
	"RightX",
	"RightY",
	"LeftTrigger",
	"RightTrigger"
};

Bool Minty::Parser<GamepadAxisEnum>::parse(StringView const str, GamepadAxisEnum &value)
{
    return Tool::try_parse_enum(str, GAMEPADAXIS_STRINGS, GAMEPADAXIS_COUNT, value);
}

String Minty::Parser<GamepadAxisEnum>::to_string(GamepadAxisEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), GAMEPADAXIS_STRINGS, GAMEPADAXIS_COUNT);
}