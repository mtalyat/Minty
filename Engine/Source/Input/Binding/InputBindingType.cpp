#include "pch.hpp"
#include "InputBindingType.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* BINDING_TYPE_ENUM_STRINGS[static_cast<Size>(InputBindingTypeEnum::Count)] = {
    "None",
    "Button",
    "Axis",
    "Axis2D"
};

Bool Minty::Parser<InputBindingTypeEnum>::parse(StringView const str, InputBindingTypeEnum &value)
{
    return Tool::try_parse_enum(str, BINDING_TYPE_ENUM_STRINGS, static_cast<Size>(InputBindingTypeEnum::Count), value);
}

String Minty::Parser<InputBindingTypeEnum>::to_string(InputBindingTypeEnum const &obj)
{
    return Tool::to_string_enum(obj, BINDING_TYPE_ENUM_STRINGS, static_cast<Size>(InputBindingTypeEnum::Count));
}
