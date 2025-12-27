#include "pch.h"
#include "NameComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<NameComponent>::serialize(Writer &writer, NameComponent const &value)
{
	writer.write("Name", name);
}

void Minty::Serializer<NameComponent>::deserialize(Reader &reader, NameComponent &value)
{
	if(!reader.read_default(value.name))
	{
		reader.read("Name", value.name);
	}
}
