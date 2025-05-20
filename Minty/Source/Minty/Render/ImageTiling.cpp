#include "pch.h"
#include "ImageTiling.h"

using namespace Minty;

String Minty::to_string(ImageTiling const obj)
{
	switch (obj)
	{
	case ImageTiling::Optimal: return "Optimal";
	case ImageTiling::Linear: return "Linear";

	default: return "";
	}
}

ImageTiling Minty::parse_to_image_tiling(String const& string)
{
	if (string == "Optimal") return ImageTiling::Optimal;
	if (string == "Linear") return ImageTiling::Linear;

	return ImageTiling();
}

Bool Minty::parse_try_image_tiling(String const& string, ImageTiling& value)
{
	value = parse_to_image_tiling(string);
	return value != ImageTiling();
}