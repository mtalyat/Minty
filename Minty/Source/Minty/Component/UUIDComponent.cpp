#include "pch.h"
#include "UUIDComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::UUIDComponent::serialize(Writer& writer) const
{
	writer.write("id", id);
}

Bool Minty::UUIDComponent::deserialize(Reader& reader)
{
	reader.read("id", id);
	return true;
}
