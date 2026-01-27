#include "pch.h"
#include "MaskComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<MaskComponent>::serialize(Writer &writer, MaskComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<MaskComponent>::deserialize(Reader &reader, MaskComponent &value)
{
	reader.read_primary("Value", value.value);
	return true;
}
