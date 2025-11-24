#include "pch.h"
#include "BufferUsage.h"

using namespace Minty;

static String const s_usageStrings[] = {
	"TransferSrc",
	"TransferDst",
	"Vertex",
	"Index",
	"Uniform"
};

String Minty::to_string(BufferUsage const obj)
{
	if (obj == BufferUsage::Undefined)
	{
		return "Undefined";
	}

	String output = "";
	Size objValue = static_cast<Size>(obj);
	Size usage = 1;
	Size const max = static_cast<Size>(BufferUsage::Max);
	for (Size index = 0; usage <= max; usage <<= 1, index++)
	{
		if (usage & objValue)
		{
			output += s_usageStrings[index] + "|";
		}
	}
	MINTY_ASSERT(output.get_size() > 0, "Invalid BufferUsage value.");
	return output.sub(0, output.get_size() - 1);
}

BufferUsage Minty::parse_to_buffer_usage(String const& string)
{
	if (string.contains("TransferSrc")) return BufferUsage::TransferSrc;
	if (string.contains("TransferDst")) return BufferUsage::TransferDst;
	if (string.contains("Vertex")) return BufferUsage::Vertex;
	if (string.contains("Index")) return BufferUsage::Index;
	if (string.contains("Uniform")) return BufferUsage::Uniform;

	return BufferUsage();
}

Bool Minty::parse_try_buffer_usage(String const& string, BufferUsage& value)
{
	value = parse_to_buffer_usage(string);
	return value != BufferUsage();
}