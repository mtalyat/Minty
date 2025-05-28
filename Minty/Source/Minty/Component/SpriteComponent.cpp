#include "pch.h"
#include "SpriteComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::SpriteComponent::serialize(Writer& writer) const
{
	writer.write("Sprite", sprite);
	writer.write("Color", color);
}

Bool Minty::SpriteComponent::deserialize(Reader& reader)
{
	reader.read("Sprite", sprite);
	reader.read("Color", color);

	return true;
}
