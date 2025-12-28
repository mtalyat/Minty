#include "pch.h"
#include "FontFlags.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size FONTFLAGS_COUNT = 2;
static constexpr Char const* FONTFLAGS_STRINGS[FONTFLAGS_COUNT] = 
{
	"Bold",
	"Italic"
};

Bool Minty::Parser<FontFlags>::parse(StringView const str, FontFlags &value)
{
    return Tool::try_parse_enum_flags(str, FONTFLAGS_STRINGS, FONTFLAGS_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<FontFlags>::to_string(FontFlags const &obj)
{
    return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(obj), FONTFLAGS_STRINGS, FONTFLAGS_COUNT);
}
