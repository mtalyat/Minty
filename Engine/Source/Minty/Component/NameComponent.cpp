#include "pch.h"
#include "NameComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<NameComponent>::serialize(Writer &writer, NameComponent const &value)
{
	writer.write("Name", value.name);
}

void Minty::Serializer<NameComponent>::deserialize(Reader &reader, NameComponent &value)
{
	reader.read("Name", value.name);
}
