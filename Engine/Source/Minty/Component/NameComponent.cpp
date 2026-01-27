#include "pch.h"
#include "NameComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<NameComponent>::serialize(Writer &writer, NameComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<NameComponent>::deserialize(Reader &reader, NameComponent &value)
{
	reader.read_primary("Name", value.name);
	return true;
}
