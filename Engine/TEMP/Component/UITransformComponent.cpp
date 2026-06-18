#include "pch.h"
#include "UITransformComponent.h"

using namespace Minty;

Bool Minty::Serializer<UITransformComponent>::serialize(Writer &writer, UITransformComponent const &value)
{
	Serializer<UITransform>::serialize(writer, value.transform);
}

Bool Minty::Serializer<UITransformComponent>::deserialize(Reader &reader, UITransformComponent &value)
{
	return Serializer<UITransform>::deserialize(reader, value.transform);
}
