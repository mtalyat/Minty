#include "pch.h"
#include "DepthMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size DEPTHMODE_COUNT = 3;
static constexpr Char const* DEPTHMODE_STRINGS[DEPTHMODE_COUNT] =
{
    "None",
    "Write",
    "Test"
};

Bool Minty::Parser<DepthMode>::parse(StringView const str, DepthMode &value)
{
    return Tool::try_parse_enum(str, DEPTHMODE_STRINGS, DEPTHMODE_COUNT, value);
}

String Minty::Parser<DepthMode>::to_string(DepthMode const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), DEPTHMODE_STRINGS, DEPTHMODE_COUNT);
}
