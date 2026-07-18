#include "pch.hpp"
#include "NameComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<NameComponent>::serialize(Writer &writer, NameComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
	return Bool();
}

Bool Minty::Serializer<NameComponent>::deserialize(Reader &reader, NameComponent &value)
{
	reader.read_primary("Name", value.name);
	return true;
}
