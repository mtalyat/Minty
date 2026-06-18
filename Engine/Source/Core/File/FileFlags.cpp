#include "pch.h"
#include "FileFlags.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size FILEFLAG_COUNT = 6;
static constexpr Char const* FILEFLAG_STRINGS[FILEFLAG_COUNT] =
{
    "Read",
    "Write",
    "Append",
    "Binary",
    "Truncate",
    "Create"
};

Bool Minty::Parser<FileFlagsEnum>::parse(StringView const str, FileFlagsEnum &value)
{
    return Tool::try_parse_enum_flags(str, FILEFLAG_STRINGS, FILEFLAG_COUNT, value);
}

String Minty::Parser<FileFlagsEnum>::to_string(FileFlagsEnum const &value)
{
    return Tool::to_string_enum_flags(value, FILEFLAG_STRINGS, FILEFLAG_COUNT);
}
