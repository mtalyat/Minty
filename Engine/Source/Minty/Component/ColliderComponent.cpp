#include "pch.h"
#include "ColliderComponent.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::ColliderComponent::serialize(Writer& writer) const
{
	collider->serialize(writer);
}

Bool Minty::ColliderComponent::deserialize(Reader& reader)
{
	collider.release(); // release any existing collider

	ColliderInfo info{};
	if (!reader.read_default(info.shape) && !reader.read("Shape", info.shape))
	{
		// could not read shape
		return false;
	}
	if (info.shape == Shape::Empty)
	{
		// read shape, but it is empty, so do nothing
		return true;
	}
	reader.read("Size", info.size);
	reader.read("Static", info.isStatic);
	if (info.shape == Shape::Custom)
	{
		Ref<Mesh> mesh;
		reader.read("Mesh", mesh);
		info.mesh = mesh;
	}
	else
	{
		info.mesh = nullptr; // no mesh for non-custom shapes
	}
	collider = Collider::create(info);
	return collider != nullptr; // return true if a collider was created
}
