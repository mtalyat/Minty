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

void Minty::Serializer<Canvas>::serialize(Writer &writer, Canvas const &value)
{
	writer.write("Resolution", value.m_resolution);
}

void Minty::Serializer<Canvas>::deserialize(Reader &reader, Canvas &value)
{
	if(!reader.read_default(value.m_resolution))
	{
		reader.read("Resolution", value.m_resolution);
	}
}