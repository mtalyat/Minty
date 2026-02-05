#include "pch.h"
#include "ImageType.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size IMAGETYPE_COUNT = 4;
static constexpr Char const* IMAGETYPE_STRINGS[IMAGETYPE_COUNT] =
{
	"Undefined",
	"D1",
	"D2",
	"D3"
};

Bool Minty::Parser<ImageType>::parse(StringView const str, ImageType &value)
{
	return Tool::try_parse_enum(str, IMAGETYPE_STRINGS, IMAGETYPE_COUNT, value);
}

String Minty::Parser<ImageType>::to_string(ImageType const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGETYPE_STRINGS, IMAGETYPE_COUNT);
}
