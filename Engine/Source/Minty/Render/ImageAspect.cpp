#include "pch.h"
#include "ImageAspect.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size IMAGEASPECT_COUNT = 3;
static constexpr Char const* IMAGEASPECT_STRINGS[IMAGEASPECT_COUNT] =
{
	"Undefined",
	"Color",
	"Depth"
};

Bool Minty::Parser<ImageAspect>::parse(StringView const str, ImageAspect &value)
{
	return Tool::try_parse_enum(str, IMAGEASPECT_STRINGS, IMAGEASPECT_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ImageAspect>::to_string(ImageAspect const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGEASPECT_STRINGS, IMAGEASPECT_COUNT);
}
