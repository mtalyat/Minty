#include "pch.hpp"
#include "FlipState.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* FLIPSTATE_STRINGS[static_cast<Size>(FlipStateEnumFlags::Count)] =
{
    "None",
    "X",
    "Y"
};

Bool Minty::Parser<FlipStateEnumFlags>::parse(StringView const str, FlipStateEnumFlags &value)
{
    return Tool::try_parse_enum_flags(str, FLIPSTATE_STRINGS, static_cast<Size>(FlipStateEnumFlags::Count), value);
}

String Minty::Parser<FlipStateEnumFlags>::to_string(FlipStateEnumFlags const &obj)
{
    return Tool::to_string_enum_flags(static_cast<Size>(obj), FLIPSTATE_STRINGS, static_cast<Size>(FlipStateEnumFlags::Count));
}
