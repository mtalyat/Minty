#include "pch.h"
#include "Filter.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size FILTER_COUNT = 3;
static constexpr Char const* FILTER_STRINGS[FILTER_COUNT] = 
{
	"Undefined",
	"Nearest",
	"Linear"
};

Bool Minty::Parser<Filter>::parse(StringView const str, Filter &value)
{
    return Tool::try_parse_enum(str, FILTER_STRINGS, FILTER_COUNT, value);
}

String Minty::Parser<Filter>::to_string(Filter const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), FILTER_STRINGS, FILTER_COUNT);
}
