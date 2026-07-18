#include "pch.h"
#include "LogMode.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size LOGMODE_COUNT = 2;
static constexpr Char const* LOGMODE_STRINGS[LOGMODE_COUNT] =
{
    "Console",
    "File"
};

Bool Minty::Parser<LogModeEnum>::parse(StringView const str, LogModeEnum &value)
{
    return Tool::try_parse_enum(str, LOGMODE_STRINGS, LOGMODE_COUNT, value);
}

String Minty::Parser<LogModeEnum>::to_string(LogModeEnum const &value)
{
    return Tool::to_string_enum(value, LOGMODE_STRINGS, LOGMODE_COUNT);
}
