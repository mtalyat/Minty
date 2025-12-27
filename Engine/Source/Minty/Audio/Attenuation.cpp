#include "pch.h"
#include "Attenuation.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size ATTENUATION_COUNT = 4;
static constexpr Char const* ATTENUATION_STRINGS[ATTENUATION_COUNT] = {
    "None",
    "InverseDistance",
    "LinearDistance",
    "ExponentialDistance"
};

Bool Minty::Parser<Attenuation>::parse(StringView const str, Attenuation &value)
{
    return Tool::try_parse_enum(str, ATTENUATION_STRINGS, ATTENUATION_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<Attenuation>::to_string(Attenuation const &value)
{
    return Tool::to_string_enum(static_cast<Size>(value), ATTENUATION_STRINGS, ATTENUATION_COUNT);
}