#include "pch.h"
#include "KeyAction.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size KEYACTION_COUNT = 3;
static constexpr Char const* KEYACTION_STRINGS[KEYACTION_COUNT] =
{
	"Up",
	"Down",
	"Hold",
};

Bool Minty::Parser<KeyAction>::parse(StringView const str, KeyAction &value)
{
    return Tool::try_parse_enum(str, KEYACTION_STRINGS, KEYACTION_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<KeyAction>::to_string(KeyAction const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), KEYACTION_STRINGS, KEYACTION_COUNT);
}
