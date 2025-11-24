#include "pch.h"
#include "ShaderCullMode.h"

using namespace Minty;

String Minty::to_string(ShaderCullMode const obj)
{
	switch (obj)
	{
	case ShaderCullMode::None: return "None";
	case ShaderCullMode::Front: return "Front";
	case ShaderCullMode::Back: return "Back";
	case ShaderCullMode::Both: return "Both";

	default: return "";
	}
}

ShaderCullMode Minty::parse_to_shader_cull_mode(String const& string)
{
	if (string == "None") return ShaderCullMode::None;
	if (string == "Front") return ShaderCullMode::Front;
	if (string == "Back") return ShaderCullMode::Back;
	if (string == "Both") return ShaderCullMode::Both;

	return ShaderCullMode();
}

Bool Minty::parse_try_shader_cull_mode(String const& string, ShaderCullMode& value)
{
	value = parse_to_shader_cull_mode(string);
	return value != ShaderCullMode();
}