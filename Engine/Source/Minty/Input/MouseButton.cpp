#include "pch.h"
#include "MouseButton.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size MOUSEBUTTON_COUNT = 8;
static constexpr Char const* MOUSEBUTTON_STRINGS[MOUSEBUTTON_COUNT] =
{
	"Button1",
	"Button2",
	"Button3",
	"Button4",
	"Button5",
	"Button6",
	"Button7",
	"Button8"
};

static constexpr Size MOUSEBUTTON_ALIAS_COUNT = 5;
static constexpr Char const* MOUSEBUTTON_ALIASES[MOUSEBUTTON_ALIAS_COUNT] =
{
	"Left",
	"Right",
	"Middle",
	"X1",
	"X2",
};

Bool Minty::Parser<MouseButton>::parse(StringView const str, MouseButton &value)
{
    // check special cases
	if(Tool::try_parse_enum(str, MOUSEBUTTON_STRINGS, MOUSEBUTTON_COUNT, value))
	{
		return true;
	}

	// check normal cases
	return Tool::try_parse_enum(str, MOUSEBUTTON_STRINGS, MOUSEBUTTON_COUNT, value);
}

String Minty::Parser<MouseButton>::to_string(MouseButton const &obj)
{
    return Tool::to_string_enum(obj, MOUSEBUTTON_STRINGS, MOUSEBUTTON_COUNT);
}
