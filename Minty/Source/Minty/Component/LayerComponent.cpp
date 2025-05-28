#include "pch.h"
#include "LayerComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::LayerComponent::serialize(Writer& writer) const
{
	writer.write("Layer", layer);
}

Bool Minty::LayerComponent::deserialize(Reader& reader)
{
	return reader.read("Layer", layer);
}
