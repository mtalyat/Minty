#include "pch.h"
#include "NameComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::NameComponent::serialize(Writer& writer) const
{
	writer.write("Name", name);
}

Bool Minty::NameComponent::deserialize(Reader& reader)
{
	reader.read("Name", name);
	return true;
}
