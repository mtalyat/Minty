#include "pch.h"
#include "Canvas.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Canvas::serialize(Writer& writer) const
{
	writer.write("resolution", m_resolution);
}

Bool Minty::Canvas::deserialize(Reader& reader)
{
	return reader.read("resolution", m_resolution);
}
