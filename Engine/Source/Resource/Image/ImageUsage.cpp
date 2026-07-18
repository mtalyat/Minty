#include "pch.hpp"
#include "ImageUsage.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* USAGE_STRINGS[static_cast<Size>(ImageUsageFlagsEnum::Count)] =
{
	"Undefined",
	"Sampled",
	"Storage",
	"Color",
	"DepthStencil",
	"TransferSrc",
	"TransferDst"
};

Bool Minty::Parser<ImageUsageFlagsEnum>::parse(StringView const str, ImageUsageFlagsEnum &value)
{
    return Tool::try_parse_enum_flags(str, USAGE_STRINGS, static_cast<Size>(ImageUsageFlagsEnum::Count), value);
}

String Minty::Parser<ImageUsageFlagsEnum>::to_string(ImageUsageFlagsEnum const &obj)
{
	return Tool::to_string_enum_flags(obj, USAGE_STRINGS, static_cast<Size>(ImageUsageFlagsEnum::Count));
}
