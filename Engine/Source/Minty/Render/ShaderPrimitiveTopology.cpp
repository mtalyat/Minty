#include "pch.h"
#include "ShaderPrimitiveTopology.h"

using namespace Minty;

String Minty::to_string(ShaderPrimitiveTopology const obj)
{
	switch (obj)
	{
	case ShaderPrimitiveTopology::PointList: return "PointList";
	case ShaderPrimitiveTopology::LineList: return "LineList";
	case ShaderPrimitiveTopology::LineStrip: return "LineStrip";
	case ShaderPrimitiveTopology::TriangleList: return "TriangleList";
	case ShaderPrimitiveTopology::TriangleStrip: return "TriangleStrip";
	case ShaderPrimitiveTopology::TriangleFan: return "TriangleFan";

	default: return "";
	}
}

ShaderPrimitiveTopology Minty::parse_to_shader_primitive_topology(String const& string)
{
	if (string == "PointList") return ShaderPrimitiveTopology::PointList;
	if (string == "LineList") return ShaderPrimitiveTopology::LineList;
	if (string == "LineStrip") return ShaderPrimitiveTopology::LineStrip;
	if (string == "TriangleList") return ShaderPrimitiveTopology::TriangleList;
	if (string == "TriangleStrip") return ShaderPrimitiveTopology::TriangleStrip;
	if (string == "TriangleFan") return ShaderPrimitiveTopology::TriangleFan;

	return ShaderPrimitiveTopology();
}

Bool Minty::parse_try_shader_primitive_topology(String const& string, ShaderPrimitiveTopology& value)
{
	value = parse_to_shader_primitive_topology(string);
	return value != ShaderPrimitiveTopology();
}