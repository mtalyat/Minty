#include "pch.h"
#include "MaskComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<MaskComponent>::serialize(Writer &writer, MaskComponent const &value)
{
	writer.write("Value", value.value);
}

void Minty::Serializer<MaskComponent>::deserialize(Reader &reader, MaskComponent &value)
{
	reader.read("Value", value.value);
}
