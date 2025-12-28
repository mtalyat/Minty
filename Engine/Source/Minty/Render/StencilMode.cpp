#include "pch.h"
#include "StencilMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size STENCILMODE_COUNT = 3;
static constexpr Char const* STENCILMODE_STRINGS[STENCILMODE_COUNT] =
{
    "None",
    "Write",
    "Test"
};

Bool Minty::Parser<StencilMode>::parse(StringView const str, StencilMode &value)
{
    return Tool::try_parse_enum(str, STENCILMODE_STRINGS, STENCILMODE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<StencilMode>::to_string(StencilMode const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), STENCILMODE_STRINGS, STENCILMODE_COUNT);
}
