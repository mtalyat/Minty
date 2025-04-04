#include "pch.h"
#include "ImageLayout.h"

using namespace Minty;

String Minty::to_string(ImageLayout const obj)
{
	switch (obj)
	{
	case ImageLayout::General: return "General";
	case ImageLayout::ColorAttachment: return "ColorAttachment";
	case ImageLayout::DepthStencilAttachment: return "DepthStencilAttachment";
	case ImageLayout::DepthStencilReadOnly: return "DepthStencilReadOnly";
	case ImageLayout::ShaderReadOnly: return "ShaderReadOnly";
	case ImageLayout::TransferSource: return "TransferSource";
	case ImageLayout::TransferDestination: return "TransferDestination";
	case ImageLayout::Preinitialized: return "Preinitialized";

	default: return "";
	}
}

ImageLayout Minty::parse_to_image_layout(String const& string)
{
	if (string == "General") return ImageLayout::General;
	if (string == "ColorAttachment") return ImageLayout::ColorAttachment;
	if (string == "DepthStencilAttachment") return ImageLayout::DepthStencilAttachment;
	if (string == "DepthStencilReadOnly") return ImageLayout::DepthStencilReadOnly;
	if (string == "ShaderReadOnly") return ImageLayout::ShaderReadOnly;
	if (string == "TransferSource") return ImageLayout::TransferSource;
	if (string == "TransferDestination") return ImageLayout::TransferDestination;
	if (string == "Preinitialized") return ImageLayout::Preinitialized;

	return ImageLayout();
}

Bool Minty::parse_try_image_layout(String const& string, ImageLayout& value)
{
	value = parse_to_image_layout(string);
	return value != ImageLayout();
}
