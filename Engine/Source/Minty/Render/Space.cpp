#include "pch.h"
#include "Space.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SPACE_COUNT = 4;
static constexpr Char const* SPACE_STRINGS[SPACE_COUNT] =
{
	"Undefined",
	"D3",
	"D2",
	"UI"
};

Bool Minty::Parser<Space>::parse(StringView const str, Space &value)
{
    return Tool::try_parse_enum(str, SPACE_STRINGS, SPACE_COUNT, value);
}

String Minty::Parser<Space>::to_string(Space const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(value), SPACE_STRINGS, SPACE_COUNT);
}
