#include "pch.h"
#include "BufferUsage.h"

using namespace Minty;

String Minty::to_string(BufferUsage const obj)
{
	switch (obj)
	{
	case BufferUsage::Transfer: return "Transfer";
	case BufferUsage::Vertex: return "Vertex";
	case BufferUsage::Index: return "Index";
	case BufferUsage::Uniform: return "Uniform";

	default: return "";
	}
}

BufferUsage Minty::parse_to_buffer_usage(String const& string)
{
	if (string == "Transfer") return BufferUsage::Transfer;
	if (string == "Vertex") return BufferUsage::Vertex;
	if (string == "Index") return BufferUsage::Index;
	if (string == "Uniform") return BufferUsage::Uniform;

	return BufferUsage();
}

Bool Minty::parse_try_buffer_usage(String const& string, BufferUsage& value)
{
	value = parse_to_buffer_usage(string);
	return value != BufferUsage();
}