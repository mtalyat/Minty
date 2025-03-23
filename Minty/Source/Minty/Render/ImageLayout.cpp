#include "pch.h"
#include "ImageLayout.h"

using namespace Minty;

String Minty::to_string(ImageLayout const obj)
{
	switch (obj)
	{
	case ImageLayout::General: return "General";
	case ImageLayout::ColorAttachmentOptimal: return "ColorAttachmentOptimal";
	case ImageLayout::DepthStencilAttachmentOptimal: return "DepthStencilAttachmentOptimal";
	case ImageLayout::DepthStencilReadOnlyOptimal: return "DepthStencilReadOnlyOptimal";
	case ImageLayout::ShaderReadOnlyOptimal: return "ShaderReadOnlyOptimal";
	case ImageLayout::TransferSourceOptimal: return "TransferSourceOptimal";
	case ImageLayout::TransferDestinationOptimal: return "TransferDestinationOptimal";
	case ImageLayout::Preinitialized: return "Preinitialized";

	default: return "";
	}
}

ImageLayout Minty::parse_to_image_layout(String const& string)
{
	if (string == "General") return ImageLayout::General;
	if (string == "ColorAttachmentOptimal") return ImageLayout::ColorAttachmentOptimal;
	if (string == "DepthStencilAttachmentOptimal") return ImageLayout::DepthStencilAttachmentOptimal;
	if (string == "DepthStencilReadOnlyOptimal") return ImageLayout::DepthStencilReadOnlyOptimal;
	if (string == "ShaderReadOnlyOptimal") return ImageLayout::ShaderReadOnlyOptimal;
	if (string == "TransferSourceOptimal") return ImageLayout::TransferSourceOptimal;
	if (string == "TransferDestinationOptimal") return ImageLayout::TransferDestinationOptimal;
	if (string == "Preinitialized") return ImageLayout::Preinitialized;

	return ImageLayout();
}

Bool Minty::parse_try_image_layout(String const& string, ImageLayout& value)
{
	value = parse_to_image_layout(string);
	return value != ImageLayout();
}
