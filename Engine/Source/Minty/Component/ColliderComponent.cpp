#include "pch.h"
#include "ColliderComponent.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Asset/AssetManager.h"

using namespace Minty;

void Minty::Serializer<ColliderComponent>::serialize(Writer &writer, ColliderComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<ColliderComponent>::deserialize(Reader &reader, ColliderComponent &value)
{
	if(!value.collider)
	{
		// no existing collider, so create new one
		ColliderInfo info{};
		reader.read_primary("Shape", info.shape);
		if (info.shape == Shape::Empty)
		{
			// read shape, but it is empty, so do nothing
			value.collider = Collider::create(info);
			return true;
		}
		if (info.shape == Shape::Custom)
		{
			AssetManager &assetManager = AssetManager::get_singleton();
			assetManager.deserialize_asset<Mesh>(reader, "Mesh", info.mesh);
		}
		reader.read("Offset", info.offset);
		reader.read("Size", info.size);
		reader.read("Static", info.isStatic);
		reader.read("Trigger", info.isTrigger);
		value.collider = Collider::create(info);
	} else
	{
		MINTY_NOT_IMPLEMENTED(); // overriding existing collider is not supported
		return false;
	}
	return true;
}