#include "pch.hpp"
#include "Conditional.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* CONDITIONAL_STRINGS[static_cast<Size>(ConditionalEnum::Count)] =
{
	"Equal",
	"NotEqual",
	"GreaterThan",
	"GreaterThanOrEqual",
	"LessThan",
	"LessThanOrEqual"
};
static constexpr Char const* CONDITIONAL_SYMBOLS[static_cast<Size>(ConditionalEnum::Count)] =
{
	"==",
	"!=",
	">",
	">=",
	"<",
	"<="
};

Bool Minty::Parser<ConditionalEnum>::parse(StringView const str, ConditionalEnum &value)
{
    Bool const result = Tool::try_parse_enum(str, CONDITIONAL_STRINGS, static_cast<Size>(ConditionalEnum::Count), value);
	if(result)
	{
		return true;
	}

	return Tool::try_parse_enum(str, CONDITIONAL_SYMBOLS, static_cast<Size>(ConditionalEnum::Count), value);
}

String Minty::Parser<ConditionalEnum>::to_string(ConditionalEnum const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(value), CONDITIONAL_STRINGS, static_cast<Size>(ConditionalEnum::Count));
}
