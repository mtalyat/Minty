#include "pch.hpp"
#include "MaskedComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<MaskedComponent>::serialize(Writer &writer, MaskedComponent const &value)
{
	writer.write("Value", value);
	return true;
}

Bool Minty::Serializer<MaskedComponent>::deserialize(Reader &reader, MaskedComponent &value)
{
	reader.read_primary("Value", value);
	return true;
}
