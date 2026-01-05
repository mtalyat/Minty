#include "pch.h"
#include "FileFlags.h"
#include "Minty/Tool/Enum.h"

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

Bool Minty::Parser<FileFlags>::parse(StringView const str, FileFlags &value)
{
    return Tool::try_parse_enum_flags(str, FILEFLAG_STRINGS, FILEFLAG_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<FileFlags>::to_string(FileFlags const &value)
{
    return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(value), FILEFLAG_STRINGS, FILEFLAG_COUNT);
}
