#include "pch.h"
#include "ImageType.h"

using namespace Minty;

String Minty::to_string(ImageType const obj)
{
	switch (obj)
	{
	case ImageType::D1: return "D1";
	case ImageType::D2: return "D2";
	case ImageType::D3: return "D3";

	default: return "";
	}
}

ImageType Minty::parse_to_image_type(String const& string)
{
	if (string == "D1") return ImageType::D1;
	if (string == "D2") return ImageType::D2;
	if (string == "D3") return ImageType::D3;

	return ImageType();
}

Bool Minty::parse_try_image_type(String const& string, ImageType& value)
{
	value = parse_to_image_type(string);
	return value != ImageType();
}