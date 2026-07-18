#include "pch.hpp"
#include "ImageTiling.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* IMAGETILING_STRINGS[static_cast<Size>(ImageTilingEnum::Count)] =
{
	"Undefined",
	"Optimal",
	"Linear"
};

Bool Minty::Parser<ImageTilingEnum>::parse(StringView const str, ImageTilingEnum &value)
{
    return Tool::try_parse_enum(str, IMAGETILING_STRINGS, static_cast<Size>(ImageTilingEnum::Count), value);
}

String Minty::Parser<ImageTilingEnum>::to_string(ImageTilingEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGETILING_STRINGS, static_cast<Size>(ImageTilingEnum::Count));
}
