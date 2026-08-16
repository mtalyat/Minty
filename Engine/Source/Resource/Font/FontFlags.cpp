#include "pch.hpp"
#include "FontFlags.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* FONTFLAGS_STRINGS[static_cast<Size>(FontFlagsEnum::Count)] = 
{
    "None",
	"Bold",
	"Italic"
};

Bool Minty::Parser<FontFlagsEnum>::parse(StringView const str, FontFlagsEnum &value)
{
    return Tool::try_parse_enum_flags(str, FONTFLAGS_STRINGS, static_cast<Size>(FontFlagsEnum::Count), value);
}

String Minty::Parser<FontFlagsEnum>::to_string(FontFlagsEnum const &obj)
{
    return Tool::to_string_enum_flags(obj, FONTFLAGS_STRINGS, static_cast<Size>(FontFlagsEnum::Count));
}
