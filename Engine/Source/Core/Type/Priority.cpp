#include "pch.hpp"
#include "Priority.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* PRIORITY_ENUM_STRINGS[static_cast<Size>(PriorityEnum::Count)] = {
    "Low",
    "Medium",
    "High"
};

Bool Parser<PriorityEnum>::parse(StringView const str, PriorityEnum &value)
{
    return Tool::try_parse_enum(str, PRIORITY_ENUM_STRINGS, static_cast<Size>(PriorityEnum::Count), value);
}

String Minty::Parser<PriorityEnum>::to_string(PriorityEnum const &obj)
{
    return Tool::to_string_enum(obj, PRIORITY_ENUM_STRINGS, static_cast<Size>(PriorityEnum::Count));
}
