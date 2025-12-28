#include "pch.h"
#include "ImagePixelFormat.h"

using namespace Minty;

static constexpr Size IMAGEPIXELFORMAT_COUNT = 5;
static constexpr Char const* IMAGEPIXELFORMAT_STRINGS[IMAGEPIXELFORMAT_COUNT] =
{
	"None",
	"Gray",
	"GrayAlpha",
	"RedGreenBlue",
	"RedGreenBlueAlpha"
};

Bool Minty::Parser<ImagePixelFormat>::parse(StringView const str, ImagePixelFormat &value)
{
    return Tool::try_parse_enum(str, IMAGEPIXELFORMAT_STRINGS, IMAGEPIXELFORMAT_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ImagePixelFormat>::to_string(ImagePixelFormat const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGEPIXELFORMAT_STRINGS, IMAGEPIXELFORMAT_COUNT);
}
