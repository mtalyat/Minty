#include "pch.h"
#include "TextureAddressMode.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* ADDRESSMODE_STRINGS[static_cast<Size>(TextureAddressModeEnum::Count)] =
{
    "Undefined",
    "Repeat",
    "MirroredRepeat",
    "ClampToEdge",
    "ClampToBorder",
    "MirroredClampToEdge"
};

Bool Minty::Parser<TextureAddressModeEnum>::parse(StringView const str, TextureAddressModeEnum &value)
{
    return Tool::try_parse_enum(str, ADDRESSMODE_STRINGS, static_cast<Size>(TextureAddressModeEnum::Count), value);
}

String Minty::Parser<TextureAddressModeEnum>::to_string(TextureAddressModeEnum const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), ADDRESSMODE_STRINGS, static_cast<Size>(TextureAddressModeEnum::Count));
}
