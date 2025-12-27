#include "pch.h"
#include "ColliderComponent.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<ColliderComponent>::serialize(Writer &writer, ColliderComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

void Minty::Serializer<ColliderComponent>::deserialize(Reader &reader, ColliderComponent &value)
{
	if(!value.collider)
	{
		// no existing collider, so create new one
		ColliderInfo info{};
		if (!reader.read_default(info.shape))
		{
			reader.read("Shape", info.shape);
		}
		if (info.shape == Shape::Empty)
		{
			// read shape, but it is empty, so do nothing
			value.collider = Collider::create(info);
			return true;
		}
		reader.read("Offset", info.offset);
		reader.read("Size", info.size);
		reader.read("Static", info.isStatic);
		reader.read("Trigger", info.isTrigger);
		if (info.shape == Shape::Custom)
		{
			reader.read("Mesh", info.mesh);
		}
		value.collider = Collider::create(info);
	} else
	{
		MINTY_NOT_IMPLEMENTED(); // overriding existing collider is not supported
	}
}
