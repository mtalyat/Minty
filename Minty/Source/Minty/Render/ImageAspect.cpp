#include "pch.h"
#include "ImageAspect.h"

using namespace Minty;

String Minty::to_string(ImageAspect const obj)
{
	switch (obj)
	{
	case ImageAspect::Color: return "Color";
	case ImageAspect::Depth: return "Depth";

	default: return "";
	}
}

ImageAspect Minty::parse_to_image_aspect(String const& string)
{
	if (string == "Color") return ImageAspect::Color;
	if (string == "Depth") return ImageAspect::Depth;

	return ImageAspect();
}

Bool Minty::parse_try_image_aspect(String const& string, ImageAspect& value)
{
	value = parse_to_image_aspect(string);
	return value != ImageAspect();
}