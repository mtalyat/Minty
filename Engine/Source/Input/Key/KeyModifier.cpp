#include "pch.h"
#include "KeyModifier.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* KEY_MODIFIER_ENUM_FLAGS_STRINGS[static_cast<Size>(KeyModifierFlagsEnum::Count)] =
{
    "None", // 0x0
    "Shift", // 0x1
    "Control", // 0x2
    "Alt", // 0x4
    "Super", // 0x8
    "CapsLock", // 0x10
    "NumLock", // 0x20
};

Bool Minty::Parser<KeyModifierFlagsEnum>::parse(StringView const str, KeyModifierFlagsEnum &value)
{
    return Tool::try_parse_enum_flags(str, KEY_MODIFIER_ENUM_FLAGS_STRINGS, static_cast<Size>(KeyModifierFlagsEnum::Count), value);
}

String Minty::Parser<KeyModifierFlagsEnum>::to_string(KeyModifierFlagsEnum const &obj)
{
    return Tool::to_string_enum_flags(obj, KEY_MODIFIER_ENUM_FLAGS_STRINGS, static_cast<Size>(KeyModifierFlagsEnum::Count));
}
