#include "pch.h"
#include "ImageLayout.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size IMAGELAYOUT_COUNT = 10;
static constexpr Char const* IMAGELAYOUT_STRINGS[IMAGELAYOUT_COUNT] =
{
	"Undefined",
	"General",
	"ColorAttachment",
	"DepthStencilAttachment",
	"DepthStencilReadOnly",
	"ShaderReadOnly",
	"TransferSource",
	"TransferDestination",
	"Preinitialized",
	"Presentation"
};

Bool Minty::Parser<ImageLayout>::parse(StringView const str, ImageLayout &value)
{
    return Tool::try_parse_enum(str, IMAGELAYOUT_STRINGS, IMAGELAYOUT_COUNT, value);
}

String Minty::Parser<ImageLayout>::to_string(ImageLayout const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGELAYOUT_STRINGS, IMAGELAYOUT_COUNT);
}
