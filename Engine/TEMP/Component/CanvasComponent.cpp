#include "pch.h"
#include "CanvasComponent.h"

using namespace Minty;

Bool Minty::Serializer<CanvasComponent>::serialize(Writer &writer, CanvasComponent const &value)
{
	Serializer<Canvas>::serialize(writer, value.canvas);
}

Bool Minty::Serializer<CanvasComponent>::deserialize(Reader &reader, CanvasComponent &value)
{
	return Serializer<Canvas>::deserialize(reader, value.canvas);
}
