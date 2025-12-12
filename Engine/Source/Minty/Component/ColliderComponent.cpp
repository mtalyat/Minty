#include "pch.h"
#include "ColliderComponent.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::ColliderComponent::serialize(Writer& writer) const
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::ColliderComponent::deserialize(Reader& reader)
{
	if(!collider)
	{
		// no existing collider, so create new one
		ColliderInfo info{};
		if (!reader.read_default(info.shape) && !reader.read("Shape", info.shape))
		{
			// could not read shape
			MINTY_ERROR_F(ErrorCode::Serialization_MissingRequired, "Shape");
			return false;
		}
		if (info.shape == Shape::Empty)
		{
			// read shape, but it is empty, so do nothing
			collider = Collider::create(info);
			return true;
		}
		reader.read("Offset", info.offset);
		reader.read("Size", info.size);
		reader.read("Static", info.isStatic);
		if (info.shape == Shape::Custom)
		{
			reader.read("Mesh", info.mesh);
		}
		collider = Collider::create(info);
	} else
	{
		MINTY_NOT_IMPLEMENTED(); // overriding existing collider is not supported
	}

	return true;
}
