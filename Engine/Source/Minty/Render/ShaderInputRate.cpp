#include "pch.h"
#include "ShaderInputRate.h"

using namespace Minty;

String Minty::to_string(ShaderInputRate const obj)
{
	switch (obj)
	{
	case ShaderInputRate::Vertex: return "Vertex";
	case ShaderInputRate::Instance: return "Instance";

	default: return "";
	}
}

ShaderInputRate Minty::parse_to_shader_input_rate(String const& string)
{
	if (string == "Vertex") return ShaderInputRate::Vertex;
	if (string == "Instance") return ShaderInputRate::Instance;

	return ShaderInputRate();
}

Bool Minty::parse_try_shader_input_rate(String const& string, ShaderInputRate& value)
{
	value = parse_to_shader_input_rate(string);
	return value != ShaderInputRate();
}