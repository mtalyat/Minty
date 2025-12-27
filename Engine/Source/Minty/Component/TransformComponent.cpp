#include "pch.h"
#include "TransformComponent.h"

using namespace Minty;

void Minty::Serializer<TransformComponent>::serialize(Writer &writer, TransformComponent const &value)
{
	Serializer<Transform>::serialize(writer, value.transform);	
}

void Minty::Serializer<TransformComponent>::deserialize(Reader &reader, TransformComponent &value)
{
	Serializer<Transform>::deserialize(reader, value.transform);
}
