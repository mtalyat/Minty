#include "pch.hpp"
#include "TransformComponent.hpp"

using namespace Minty;

Bool Minty::Serializer<TransformComponent>::serialize(Writer &writer, TransformComponent const &value)
{
	Serializer<Transform>::serialize(writer, value.transform);
	return true;
}

Bool Minty::Serializer<TransformComponent>::deserialize(Reader &reader, TransformComponent &value)
{
	return Serializer<Transform>::deserialize(reader, value.transform);
}
