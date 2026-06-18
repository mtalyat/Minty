#include "pch.h"
#include "BufferUsage.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size BUFFERUSAGE_COUNT = static_cast<Size>(BufferUsageFlagsEnum::Count);
static constexpr Char const* BUFFERUSAGE_STRINGS[BUFFERUSAGE_COUNT] = {
	"TransferSrc",
	"TransferDst",
	"Vertex",
	"Index",
	"Uniform"
};

Bool Minty::Parser<BufferUsageFlagsEnum>::parse(StringView const str, BufferUsageFlagsEnum &value)
{
    return Tool::try_parse_enum_flags(str, BUFFERUSAGE_STRINGS, BUFFERUSAGE_COUNT, value);
}

String Minty::Parser<BufferUsageFlagsEnum>::to_string(BufferUsageFlagsEnum const &obj)
{
	return Tool::to_string_enum_flags(obj, BUFFERUSAGE_STRINGS, BUFFERUSAGE_COUNT);
}
