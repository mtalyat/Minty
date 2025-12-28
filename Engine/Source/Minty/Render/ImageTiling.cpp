#include "pch.h"
#include "ImageTiling.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size IMAGETILING_COUNT = 3;
static constexpr Char const* IMAGETILING_STRINGS[IMAGETILING_COUNT] =
{
	"Undefined",
	"Optimal",
	"Linear"
};

Bool Minty::Parser<ImageTiling>::parse(StringView const str, ImageTiling &value)
{
    return Tool::try_parse_enum(str, IMAGETILING_STRINGS, IMAGETILING_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ImageTiling>::to_string(ImageTiling const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGETILING_STRINGS, IMAGETILING_COUNT);
}
