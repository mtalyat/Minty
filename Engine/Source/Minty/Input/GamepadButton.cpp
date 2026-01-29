#include "pch.h"
#include "GamepadButton.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size GAMEPADBUTTON_COUNT = 15;
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

Bool Minty::Parser<GamepadButton>::parse(StringView const str, GamepadButton &value)
{
    return Tool::try_parse_enum(str, GAMEPADBUTTON_STRINGS, GAMEPADBUTTON_COUNT, value);
}

String Minty::Parser<GamepadButton>::to_string(GamepadButton const& obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), GAMEPADBUTTON_STRINGS, GAMEPADBUTTON_COUNT);
}
