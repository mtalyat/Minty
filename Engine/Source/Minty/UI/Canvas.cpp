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
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Canvas>::deserialize(Reader &reader, Canvas &value)
{
	reader.read_primary("Resolution", value.m_resolution);
	return true;
}