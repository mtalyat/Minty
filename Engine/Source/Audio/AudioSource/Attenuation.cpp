#include "pch.h"
#include "Attenuation.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* ATTENUATION_STRINGS[static_cast<Size>(AttenuationEnum::Count)] = {
    "None",
    "InverseDistance",
    "LinearDistance",
    "ExponentialDistance"
};

Bool Minty::Parser<AttenuationEnum>::parse(StringView const str, AttenuationEnum &value)
{
    return Tool::try_parse_enum(str, ATTENUATION_STRINGS, static_cast<Size>(AttenuationEnum::Count), value);
}

String Minty::Parser<AttenuationEnum>::to_string(AttenuationEnum const &value)
{
    return Tool::to_string_enum(value, ATTENUATION_STRINGS, static_cast<Size>(AttenuationEnum::Count));
}
