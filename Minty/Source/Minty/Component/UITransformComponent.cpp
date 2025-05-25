#include "pch.h"
#include "UITransformComponent.h"

using namespace Minty;

void Minty::UITransformComponent::serialize(Writer& writer) const
{
	transform.serialize(writer);
}

Bool Minty::UITransformComponent::deserialize(Reader& reader)
{
	return transform.deserialize(reader);
}
