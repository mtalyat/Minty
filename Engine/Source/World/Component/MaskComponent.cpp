#include "pch.h"
#include "MaskComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<MaskComponent>::serialize(Writer &writer, MaskComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<MaskComponent>::deserialize(Reader &reader, MaskComponent &value)
{
	reader.read_primary("Value", value.mask);
	return true;
}
