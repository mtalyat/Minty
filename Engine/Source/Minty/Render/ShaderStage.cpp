#include "pch.h"
#include "ShaderStage.h"

using namespace Minty;

String Minty::to_string(ShaderStage const obj)
{
	switch (obj)
	{
	case ShaderStage::Vertex: return "Vertex";
	case ShaderStage::Fragment: return "Fragment";

	default: return "";
	}
}

ShaderStage Minty::parse_to_shader_stage(String const& string)
{
	if (string == "Vertex") return ShaderStage::Vertex;
	if (string == "Fragment") return ShaderStage::Fragment;

	return ShaderStage();
}

Bool Minty::parse_try_shader_stage(String const& string, ShaderStage& value)
{
	value = parse_to_shader_stage(string);
	return value != ShaderStage();
}