#include "pch.h"
#include "ImagePixelFormat.h"

using namespace Minty;

String Minty::to_string(ImagePixelFormat const obj)
{
	switch (obj)
	{
	case ImagePixelFormat::Gray: return "Gray";
	case ImagePixelFormat::GrayAlpha: return "GrayAlpha";
	case ImagePixelFormat::RedGreenBlue: return "RedGreenBlue";
	case ImagePixelFormat::RedGreenBlueAlpha: return "RedGreenBlueAlpha";

	default: return "";
	}
}

ImagePixelFormat Minty::parse_to_image_pixel_format(String const& string)
{
	if (string == "Gray") return ImagePixelFormat::Gray;
	if (string == "GrayAlpha") return ImagePixelFormat::GrayAlpha;
	if (string == "RedGreenBlue") return ImagePixelFormat::RedGreenBlue;
	if (string == "RedGreenBlueAlpha") return ImagePixelFormat::RedGreenBlueAlpha;

	return ImagePixelFormat();
}

Bool Minty::parse_try_image_pixel_format(String const& string, ImagePixelFormat& value)
{
	value = parse_to_image_pixel_format(string);
	return value != ImagePixelFormat();
}