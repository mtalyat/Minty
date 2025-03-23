#include "pch.h"
#include "ImageAddressMode.h"

using namespace Minty;

String Minty::to_string(ImageAddressMode const obj)
{
	switch (obj)
	{
	case ImageAddressMode::Repeat: return "Repeat";
	case ImageAddressMode::MirroredRepeat: return "MirroredRepeat";
	case ImageAddressMode::ClampToEdge: return "ClampToEdge";
	case ImageAddressMode::ClampToBorder: return "ClampToBorder";
	case ImageAddressMode::MirroredClampToEdge: return "MirroredClampToEdge";

	default: return "";
	}
}

ImageAddressMode Minty::parse_to_image_address_mode(String const& string)
{
	if (string == "Repeat") return ImageAddressMode::Repeat;
	if (string == "MirroredRepeat") return ImageAddressMode::MirroredRepeat;
	if (string == "ClampToEdge") return ImageAddressMode::ClampToEdge;
	if (string == "ClampToBorder") return ImageAddressMode::ClampToBorder;
	if (string == "MirroredClampToEdge") return ImageAddressMode::MirroredClampToEdge;

	return ImageAddressMode();
}

Bool Minty::parse_try_image_address_mode(String const& string, ImageAddressMode& value)
{
	value = parse_to_image_address_mode(string);
	return value != ImageAddressMode();
}