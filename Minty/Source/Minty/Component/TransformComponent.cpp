#include "pch.h"
#include "TransformComponent.h"

using namespace Minty;

void Minty::TransformComponent::serialize(Writer& writer) const
{
	transform.serialize(writer);
}

Bool Minty::TransformComponent::deserialize(Reader& reader)
{
	return transform.deserialize(reader);
}
