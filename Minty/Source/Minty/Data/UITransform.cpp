#include "pch.h"
#include "UITransform.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::UITransform::serialize(Writer& writer) const
{
	writer.write("anchorMode", m_anchorMode);
	writer.write("x", x);
	writer.write("y", y);
	writer.write("z", z);
	writer.write("width", width);
	writer.write("height", height);
}

Bool Minty::UITransform::deserialize(Reader& reader)
{
	reader.read("anchorMode", m_anchorMode);
	if (!reader.read("x", x))
	{
		reader.read("left", x);
	}
	if (!reader.read("y", y))
	{
		reader.read("top", y);
	}
	if (!reader.read("z", z))
	{
		reader.read("depth", z);
	}
	if (!reader.read("width", width))
	{
		reader.read("right", width);
	}
	if (!reader.read("height", height))
	{
		reader.read("bottom", height);
	}
	return true;
}
