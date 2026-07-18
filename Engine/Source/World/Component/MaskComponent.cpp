#include "pch.hpp"
#include "MaskComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

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
