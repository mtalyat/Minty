#include "Constraints.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size CONSTRAINT_COUNT = 3;
static constexpr Char const* CONSTRAINT_STRINGS[CONSTRAINT_COUNT] = {
    "X",
    "Y",
    "Z"
};

Bool Minty::Parser<Constraints>::parse(StringView const str, Constraints &value)
{
    return Tool::try_parse_enum_flags(str, CONSTRAINT_STRINGS, CONSTRAINT_COUNT, value);
}

String Minty::Parser<Constraints>::to_string(Constraints const &obj)
{
    return Tool::to_string_enum_flags(obj, CONSTRAINT_STRINGS, CONSTRAINT_COUNT);
}
