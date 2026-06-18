#include "pch.h"
#include "Combine.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size COMBINE_COUNT = 6;
static constexpr Char const* COMBINE_STRINGS[COMBINE_COUNT] = {
    "None",
    "Add",
    "Multiply",
    "Average",
    "Max",
    "Min"
};

Bool Minty::Parser<Combine>::parse(StringView const str, Combine &value)
{
    return Tool::try_parse_enum(str, COMBINE_STRINGS, COMBINE_COUNT, value);
}

String Minty::Parser<Combine>::to_string(Combine const &value)
{
    return Tool::to_string_enum(value, COMBINE_STRINGS, COMBINE_COUNT);   
}