#include "pch.h"
#include "ImageUsage.h"

using namespace Minty;

String Minty::to_string(ImageUsage const obj)
{
	switch (obj)
	{
	case ImageUsage::Sampled: return "Sampled";
	case ImageUsage::Storage: return "Storage";
	case ImageUsage::Color: return "Color";
	case ImageUsage::DepthStencil: return "DepthStencil";

	default: return "";
	}
}

ImageUsage Minty::parse_to_image_usage(String const& string)
{
	if (string == "Sampled") return ImageUsage::Sampled;
	if (string == "Storage") return ImageUsage::Storage;
	if (string == "Color") return ImageUsage::Color;
	if (string == "DepthStencil") return ImageUsage::DepthStencil;

	return ImageUsage();
}

Bool Minty::parse_try_image_usage(String const& string, ImageUsage& value)
{
	value = parse_to_image_usage(string);
	return value != ImageUsage();
}