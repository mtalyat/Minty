#include "pch.hpp"
#include "TextureFilter.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* TEXTUREFILTER_STRINGS[static_cast<Size>(TextureFilterEnum::Count)] =
{
    "Undefined",
    "Nearest",
    "Linear"
};

Bool Minty::Parser<TextureFilterEnum>::parse(StringView const str, TextureFilterEnum &value)
{
    return Tool::try_parse_enum(str, TEXTUREFILTER_STRINGS, static_cast<Size>(TextureFilterEnum::Count), value);
}

String Minty::Parser<TextureFilterEnum>::to_string(TextureFilterEnum const &obj)
{
    return Tool::to_string_enum(obj, TEXTUREFILTER_STRINGS, static_cast<Size>(TextureFilterEnum::Count));
}
