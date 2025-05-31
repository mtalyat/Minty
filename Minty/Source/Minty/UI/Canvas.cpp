#include "pch.h"
#include "Canvas.h"
#include "Minty/Core/Constant.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Canvas::Canvas()
	: m_resolution(
		DEFAULT_CANVAS_RESOLUTION_X,
		DEFAULT_CANVAS_RESOLUTION_Y)
{
}

void Minty::Canvas::serialize(Writer& writer) const
{
	writer.write("Resolution", m_resolution);
}

Bool Minty::Canvas::deserialize(Reader& reader)
{
	return reader.read("Resolution", m_resolution);
}
