#include "pch.h"
#include "MaskedComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::MaskedComponent::serialize(Writer& writer) const
{
	writer.write("Value", value);
}

Bool Minty::MaskedComponent::deserialize(Reader& reader)
{
	return reader.read_default(value) || reader.read("Value", value);
}
