#include "pch.h"
#include "Conditional.h"
#include "Minty/Data/Scope.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size CONDITIONAL_COUNT = 6;
static constexpr Char const* CONDITIONAL_STRINGS[CONDITIONAL_COUNT] =
{
	"Equal",
	"NotEqual",
	"GreaterThan",
	"GreaterThanOrEqual",
	"LessThan",
	"LessThanOrEqual"
};
static constexpr Char const* CONDITIONAL_SYMBOLS[CONDITIONAL_COUNT] =
{
	"==",
	"!=",
	">",
	">=",
	"<",
	"<="
};

Bool Minty::Parser<Conditional>::parse(StringView const str, Conditional &value)
{
    Bool const result = Tool::try_parse_enum(str, CONDITIONAL_STRINGS, CONDITIONAL_COUNT, value);
	if(result)
	{
		return true;
	}

	return Tool::try_parse_enum(str, CONDITIONAL_SYMBOLS, CONDITIONAL_COUNT, value);
}

String Minty::Parser<Conditional>::to_string(Conditional const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(value), CONDITIONAL_STRINGS, CONDITIONAL_COUNT);
}
