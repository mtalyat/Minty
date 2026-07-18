#include "pch.hpp"
#include "ImageLayout.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* IMAGELAYOUT_STRINGS[static_cast<Size>(ImageLayoutEnum::Count)] =
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

Bool Minty::Parser<ImageLayoutEnum>::parse(StringView const str, ImageLayoutEnum &value)
{
    return Tool::try_parse_enum(str, IMAGELAYOUT_STRINGS, static_cast<Size>(ImageLayoutEnum::Count), value);
}

String Minty::Parser<ImageLayoutEnum>::to_string(ImageLayoutEnum const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), IMAGELAYOUT_STRINGS, static_cast<Size>(ImageLayoutEnum::Count));
}
