#include "pch.h"
#include "UITransformComponent.h"

using namespace Minty;

void Minty::Serializer<UITransformComponent>::serialize(Writer &writer, UITransformComponent const &value)
{
	Serializer<UITransform>::serialize(writer, value.transform);
}

void Minty::Serializer<UITransformComponent>::deserialize(Reader &reader, UITransformComponent &value)
{
	Serializer<UITransform>::deserialize(reader, value.transform);
}
