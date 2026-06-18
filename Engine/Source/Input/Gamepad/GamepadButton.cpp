#include "pch.h"
#include "GamepadButton.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size GAMEPADBUTTON_COUNT = static_cast<Size>(GamepadButtonEnum::Count);
static constexpr Char const* GAMEPADBUTTON_STRINGS[GAMEPADBUTTON_COUNT] =
{
	"ButtonSouth",
	"ButtonEast",
	"ButtonWest",
	"ButtonNorth",
	"LeftBumper",
	"RightBumper",
	"Back",
	"Start",
	"Home",
	"LeftThumb",
	"RightThumb",
	"DpadUp",
	"DpadRight",
	"DpadDown",
	"DpadLeft"
};

Bool Minty::Parser<GamepadButtonEnum>::parse(StringView const str, GamepadButtonEnum &value)
{
    return Tool::try_parse_enum(str, GAMEPADBUTTON_STRINGS, GAMEPADBUTTON_COUNT, value);
}

String Minty::Parser<GamepadButtonEnum>::to_string(GamepadButtonEnum const& obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), GAMEPADBUTTON_STRINGS, GAMEPADBUTTON_COUNT);
}
