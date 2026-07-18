#include "EventState.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const *EVENT_STATE_ENUM_STRINGS[static_cast<Size>(EventStateEnum::Count)] =
    {
        "Unhandled",
        "Handled",
        "Canceled"};

Bool Minty::Parser<EventStateEnum>::parse(StringView const str, EventStateEnum &value)
{
    return Tool::try_parse_enum(str, EVENT_STATE_ENUM_STRINGS, static_cast<Size>(EventStateEnum::Count), value);
}

String Minty::Parser<EventStateEnum>::to_string(EventStateEnum const &value)
{
    return Tool::to_string_enum(value, EVENT_STATE_ENUM_STRINGS, static_cast<Size>(EventStateEnum::Count));
}
