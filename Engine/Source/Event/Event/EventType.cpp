#include "EventType.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const *EVENT_TYPE_ENUM_STRINGS[static_cast<Size>(EventTypeEnum::Count)] =
    {
        "Undefined",
        "WindowClose",
        "WindowResize",
        "Key",
        "MouseButton",
        "MouseMove",
        "MouseScroll",
        "GamepadConnect",
        "GamepadDisconnect",
        "GamepadButton",
        "GamepadAxis"};

Bool Minty::Parser<EventTypeEnum>::parse(StringView const str, EventTypeEnum &value)
{
    return Tool::try_parse_enum(str, EVENT_TYPE_ENUM_STRINGS, static_cast<Size>(EventTypeEnum::Count), value);
}

String Minty::Parser<EventTypeEnum>::to_string(EventTypeEnum const &value)
{
    return Tool::to_string_enum(value, EVENT_TYPE_ENUM_STRINGS, static_cast<Size>(EventTypeEnum::Count));
}
