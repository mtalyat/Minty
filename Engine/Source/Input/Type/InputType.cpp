#include "pch.hpp"
#include "InputType.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* INPUT_TYPE_ENUM_STRINGS[static_cast<Size>(InputTypeEnum::Count)] = {
    "None",
    "Key",
    "MouseButton",
    "MouseMove",
    "MouseScroll",
    "GamepadButton",
    "GamepadAxis"
};

Bool Minty::Parser<InputTypeEnum>::parse(StringView const str, InputTypeEnum &value)
{
    return Tool::try_parse_enum(str, INPUT_TYPE_ENUM_STRINGS, static_cast<Size>(InputTypeEnum::Count), value);
}

String Minty::Parser<InputTypeEnum>::to_string(InputTypeEnum const &obj)
{
    return Tool::to_string_enum(obj, INPUT_TYPE_ENUM_STRINGS, static_cast<Size>(InputTypeEnum::Count));
}
