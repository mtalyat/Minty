#include "pch.h"
#include "ImageUsage.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size USAGE_COUNT = 6;
static constexpr Char const* USAGE_STRINGS[USAGE_COUNT] =
{
	"Sampled",
	"Storage",
	"Color",
	"DepthStencil",
	"TransferSrc",
	"TransferDst"
};

Bool Minty::Parser<ImageUsage>::parse(StringView const str, ImageUsage &value)
{
    return Tool::try_parse_enum_flags(str, USAGE_STRINGS, USAGE_COUNT, value);
}

String Minty::Parser<ImageUsage>::to_string(ImageUsage const &obj)
{
	return Tool::to_string_enum_flags(obj, USAGE_STRINGS, USAGE_COUNT);
}
