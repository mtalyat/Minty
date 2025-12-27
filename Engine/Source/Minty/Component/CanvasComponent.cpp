#include "pch.h"
#include "CanvasComponent.h"

using namespace Minty;

void Minty::Serializer<CanvasComponent>::serialize(Writer &writer, CanvasComponent const &value)
{
	Serializer<Canvas>::serialize(writer, value.canvas);
}

void Minty::Serializer<CanvasComponent>::deserialize(Reader &reader, CanvasComponent &value)
{
	Serializer<Canvas>::deserialize(reader, value.canvas);
}
