#include "pch.h"
#include "MaskedComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<MaskedComponent>::serialize(Writer &writer, MaskedComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<MaskedComponent>::deserialize(Reader &reader, MaskedComponent &value)
{
	reader.read_primary("Value", value.value);
	return true;
}
