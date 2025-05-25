#include "pch.h"
#include "SpriteComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::SpriteComponent::serialize(Writer& writer) const
{
	writer.write("sprite", sprite);
	writer.write("color", color);
}

Bool Minty::SpriteComponent::deserialize(Reader& reader)
{
	reader.read("sprite", sprite);
	reader.read("color", color);

	return true;
}
