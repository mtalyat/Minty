#include "pch.h"
#include "ColliderComponent.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Minty/Render/Mesh.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"
#include "Minty/Asset/AssetManager.h"

using namespace Minty;

Bool Minty::Serializer<ColliderComponent>::serialize(Writer &writer, ColliderComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<ColliderComponent>::deserialize(Reader &reader, ColliderComponent &value)
{
	if(!value.collider)
	{
		AssetManager &assetManager = AssetManager::get_singleton();

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
			assetManager.deserialize_asset<Mesh>(reader, "Mesh", info.mesh);
		}
		assetManager.deserialize_asset<PhysicsMaterial>(reader, "Material", info.material);
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