#include "pch.h"
#include "ImageAspect.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* IMAGE_ASPECT_STRINGS[static_cast<Size>(ImageAspectFlagsEnum::Count)] =
{
	"Undefined",
	"Color",
	"Depth"
};

Bool Minty::Parser<ImageAspectFlagsEnum>::parse(StringView const str, ImageAspectFlagsEnum &value)
{
	return Tool::try_parse_enum_flags(str, IMAGE_ASPECT_STRINGS, static_cast<Size>(ImageAspectFlagsEnum::Count), value);
}

String Minty::Parser<ImageAspectFlagsEnum>::to_string(ImageAspectFlagsEnum const &obj)
{
    return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(obj), IMAGE_ASPECT_STRINGS, static_cast<Size>(ImageAspectFlagsEnum::Count));
}
