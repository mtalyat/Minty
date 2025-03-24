#include "pch.h"
#include "ShaderFrontFace.h"

using namespace Minty;

String Minty::to_string(ShaderFrontFace const obj)
{
	switch (obj)
	{
	case ShaderFrontFace::CounterClockwise: return "CounterClockwise";
	case ShaderFrontFace::Clockwise: return "Clockwise";

	default: return "";
	}
}

ShaderFrontFace Minty::parse_to_shader_front_face(String const& string)
{
	if (string == "CounterClockwise") return ShaderFrontFace::CounterClockwise;
	if (string == "Clockwise") return ShaderFrontFace::Clockwise;

	return ShaderFrontFace();
}

Bool Minty::parse_try_shader_front_face(String const& string, ShaderFrontFace& value)
{
	value = parse_to_shader_front_face(string);
	return value != ShaderFrontFace();
}