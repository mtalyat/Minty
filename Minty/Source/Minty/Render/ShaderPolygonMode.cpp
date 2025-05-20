#include "pch.h"
#include "ShaderPolygonMode.h"

using namespace Minty;

String Minty::to_string(ShaderPolygonMode const obj)
{
	switch (obj)
	{
	case ShaderPolygonMode::Fill: return "Fill";
	case ShaderPolygonMode::Line: return "Line";
	case ShaderPolygonMode::Point: return "Point";

	default: return "";
	}
}

ShaderPolygonMode Minty::parse_to_shader_polygon_mode(String const& string)
{
	if (string == "Fill") return ShaderPolygonMode::Fill;
	if (string == "Line") return ShaderPolygonMode::Line;
	if (string == "Point") return ShaderPolygonMode::Point;

	return ShaderPolygonMode();
}

Bool Minty::parse_try_shader_polygon_mode(String const& string, ShaderPolygonMode& value)
{
	value = parse_to_shader_polygon_mode(string);
	return value != ShaderPolygonMode();
}