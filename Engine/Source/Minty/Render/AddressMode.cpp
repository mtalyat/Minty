#include "pch.h"
#include "AddressMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size ADDRESSMODE_COUNT = 6;
static constexpr Char const* ADDRESSMODE_STRINGS[ADDRESSMODE_COUNT] =
{
    "Undefined",
    "Repeat",
    "MirroredRepeat",
    "ClampToEdge",
    "ClampToBorder",
    "MirroredClampToEdge"
};

Bool Minty::Parser<AddressMode>::parse(StringView const str, AddressMode &value)
{
    return Tool::try_parse_enum(str, ADDRESSMODE_STRINGS, ADDRESSMODE_COUNT, value);
}

String Minty::Parser<AddressMode>::to_string(AddressMode const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), ADDRESSMODE_STRINGS, ADDRESSMODE_COUNT);
}
