#include "pch.hpp"
#include "Anchor.hpp"
#include "Core/Tool/Enum.hpp"

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

Bool Minty::Parser<AnchorEnumFlags>::parse(StringView const str, AnchorEnumFlags &value)
{
	// check aliases
	if (str == "Vertical")
	{
		value = AnchorEnumFlags::Vertical;
		return true;
	}
	else if (str == "Horizontal")
	{
		value = AnchorEnumFlags::Horizontal;
		return true;
	} else if (str == "All")
	{
		value = AnchorEnumFlags::All;
		return true;
	}

    return Tool::try_parse_enum_flags(str, ANCHORMODE_STRINGS, ANCHORMODE_COUNT, value);
}

String Minty::Parser<AnchorEnumFlags>::to_string(AnchorEnumFlags const &value)
{
	// check aliases
	if (value == AnchorEnumFlags::Vertical)
	{
		return "Vertical";
	}
	else if (value == AnchorEnumFlags::Horizontal)
	{
		return "Horizontal";
	}
	else if (value == AnchorEnumFlags::All)
	{
		return "All";
	}

	return Tool::to_string_enum_flags(value, ANCHORMODE_STRINGS, ANCHORMODE_COUNT);
}