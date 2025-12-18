#include "pch.h"
#include "MaskComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::MaskComponent::serialize(Writer& writer) const
{
	writer.write("Value", value);
}

Bool Minty::MaskComponent::deserialize(Reader& reader)
{
	return reader.read_default(value) || reader.read("Value", value);
}
