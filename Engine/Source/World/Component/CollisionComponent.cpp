#include "pch.hpp"
#include "CollisionComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Collision/Manager/CollisionManager.hpp"

using namespace Minty;

Bool Minty::Serializer<CollisionComponent>::serialize(Writer &writer, CollisionComponent const &value)
{
	writer.write("Layer", value);
	return true;
}

Bool Minty::Serializer<CollisionComponent>::deserialize(Reader &reader, CollisionComponent &value)
{
	// read the name of the layer
	String layerName;
	if (reader.read_primary("Layer", layerName))
	{
		// get the layer from the name
		CollisionManager& collisionManager = CollisionManager::get_singleton();
		if (collisionManager.is_valid(layerName))
		{
			value.layer = collisionManager.get_collision(layerName);
		} else
		{
			MINTY_ERROR_A(ErrorCodeEnum::Serialization_InvalidValue, layerName.get_data());
			value.layer = COLLISION_DEFAULT;
		}
	}
	return true;
}
	