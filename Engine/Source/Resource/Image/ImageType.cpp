#include "pch.h"
#include "ImageType.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* IMAGETYPE_STRINGS[static_cast<Size>(ImageTypeEnum::Count)] =
{
	"Undefined",
	"D1",
	"D2",
	"D3"
};

Bool Minty::Parser<ImageTypeEnum>::parse(StringView const str, ImageTypeEnum &value)
{
	return Tool::try_parse_enum(str, IMAGETYPE_STRINGS, static_cast<Size>(ImageTypeEnum::Count), value);
}

String Minty::Parser<ImageTypeEnum>::to_string(ImageTypeEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGETYPE_STRINGS, static_cast<Size>(ImageTypeEnum::Count));
}
