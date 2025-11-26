#include "pch.h"
#include "ImageUsage.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

static String const s_usageStrings[] = {
	"Sampled",
	"Storage",
	"Color",
	"DepthStencil",
	"TransferSrc",
	"TransferDst"
};

String Minty::to_string(ImageUsage const obj)
{
	if (obj == ImageUsage::Undefined)
	{
		return "Undefined";
	}

	String output = "";
	Size objValue = static_cast<Size>(obj);
	Size usage = 1;
	Size const max = static_cast<Size>(ImageUsage::Max);
	for (Size index = 0; usage <= max; usage <<= 1, index++)
	{
		if (usage & objValue)
		{
			output += s_usageStrings[index] + "|";
		}
	}
	MINTY_ASSERT(output.get_size() > 0, ErrorCode::Serialization_Failed);
	return output.sub(0, output.get_size() - 1);
}

ImageUsage Minty::parse_to_image_usage(String const& string)
{
	ImageUsage usage = ImageUsage::Undefined;
	if (string.contains("Sampled")) usage |= ImageUsage::Sampled;
	if (string.contains("Storage")) usage |= ImageUsage::Storage;
	if (string.contains("Color")) usage |= ImageUsage::Color;
	if (string.contains("DepthStencil")) usage |= ImageUsage::DepthStencil;
	if (string.contains("TransferSrc")) usage |= ImageUsage::TransferSrc;
	if (string.contains("TransferDst")) usage |= ImageUsage::TransferDst;
	return usage;
}

Bool Minty::parse_try_image_usage(String const& string, ImageUsage& value)
{
	value = parse_to_image_usage(string);
	return value != ImageUsage();
}