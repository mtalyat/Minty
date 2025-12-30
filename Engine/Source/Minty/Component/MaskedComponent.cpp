#include "pch.h"
#include "MaskedComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<MaskedComponent>::serialize(Writer &writer, MaskedComponent const &value)
{
	writer.write("Value", value.value);
}

void Minty::Serializer<MaskedComponent>::deserialize(Reader &reader, MaskedComponent &value)
{
	reader.read("Value", value.value);
}
