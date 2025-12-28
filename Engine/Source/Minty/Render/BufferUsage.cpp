#include "pch.h"
#include "BufferUsage.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size BUFFERUSAGE_COUNT = 5;
static constexpr Char const* BUFFERUSAGE_STRINGS[BUFFERUSAGE_COUNT] = {
	"TransferSrc",
	"TransferDst",
	"Vertex",
	"Index",
	"Uniform"
};

Bool Minty::Parser<BufferUsage>::parse(StringView const str, BufferUsage &value)
{
    return Tool::try_parse_enum_flags(str, BUFFERUSAGE_STRINGS, BUFFERUSAGE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<BufferUsage>::to_string(BufferUsage const &obj)
{
	return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(obj), BUFFERUSAGE_STRINGS, BUFFERUSAGE_COUNT);
}
