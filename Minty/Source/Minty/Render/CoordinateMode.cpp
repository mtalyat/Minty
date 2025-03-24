#include "pch.h"
#include "CoordinateMode.h"

using namespace Minty;

String Minty::to_string(CoordinateMode const obj)
{
	switch (obj)
	{
	case CoordinateMode::Normalized: return "Normalized";
	case CoordinateMode::Pixel: return "Pixel";

	default: return "";
	}
}

CoordinateMode Minty::parse_to_coordinate_mode(String const& string)
{
	if (string == "Normalized") return CoordinateMode::Normalized;
	if (string == "Pixel") return CoordinateMode::Pixel;

	return CoordinateMode();
}

Bool Minty::parse_try_coordinate_mode(String const& string, CoordinateMode& value)
{
	value = parse_to_coordinate_mode(string);
	return value != CoordinateMode();
}