#include "pch.h"
#include "AnchorMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size ANCHORMODE_COUNT = 6;
static constexpr Char const* ANCHORMODE_STRINGS[ANCHORMODE_COUNT] =
{
	"Top",
	"Middle",
	"Bottom",
	"Left",
	"Center",
	"Right"
};

Bool Minty::Parser<AnchorMode>::parse(StringView const str, AnchorMode &value)
{
	// check aliases
	if (str == "Vertical")
	{
		value = AnchorMode::Vertical;
		return true;
	}
	else if (str == "Horizontal")
	{
		value = AnchorMode::Horizontal;
		return true;
	} else if (str == "All")
	{
		value = AnchorMode::All;
		return true;
	}

    return Tool::try_parse_enum_flags(str, ANCHORMODE_STRINGS, ANCHORMODE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<AnchorMode>::to_string(AnchorMode const &value)
{
	// check aliases
	if (value == AnchorMode::Vertical)
	{
		return "Vertical";
	}
	else if (value == AnchorMode::Horizontal)
	{
		return "Horizontal";
	}
	else if (value == AnchorMode::All)
	{
		return "All";
	}

	return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(value), ANCHORMODE_STRINGS, ANCHORMODE_COUNT);
}