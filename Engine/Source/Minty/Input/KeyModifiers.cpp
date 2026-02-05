#include "pch.h"
#include "KeyModifiers.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size KEYMODIFIERS_COUNT = 6;
static constexpr Char const* KEYMODIFIERS_STRINGS[KEYMODIFIERS_COUNT] =
{
	"Shift",
	"Control",
	"Alt",
	"Super",
	"CapsLock",
	"NumLock"
};

Bool Minty::Parser<KeyModifiers>::parse(StringView const str, KeyModifiers &value)
{
    return Tool::try_parse_enum_flags(str, KEYMODIFIERS_STRINGS, KEYMODIFIERS_COUNT, value);
}

String Minty::Parser<KeyModifiers>::to_string(KeyModifiers const &obj)
{
    return Tool::to_string_enum_flags(obj, KEYMODIFIERS_STRINGS, KEYMODIFIERS_COUNT);
}
