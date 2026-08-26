#include "pch.hpp"
#include "CanvasComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<CanvasComponent>::serialize(Writer &writer, CanvasComponent const &value)
{
	writer.write("Resolution", value.resolution);
	writer.write("ResizeMode", value.resizeMode);

	return true;
}

Bool Minty::Serializer<CanvasComponent>::deserialize(Reader &reader, CanvasComponent &value)
{
	reader.read("Resolution", value.resolution);
	reader.read("ResizeMode", value.resizeMode);

	return true;
}
