#include "pch.h"
#include "TransformComponent.h"

using namespace Minty;

Bool Minty::Serializer<TransformComponent>::serialize(Writer &writer, TransformComponent const &value)
{
	Serializer<Transform>::serialize(writer, value.transform);	
}

Bool Minty::Serializer<TransformComponent>::deserialize(Reader &reader, TransformComponent &value)
{
	return Serializer<Transform>::deserialize(reader, value.transform);
}
