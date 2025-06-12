#include "pch.h"
#include "ColliderComponent.h"
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

	ColliderBuilder builder{};
	if (!reader.read_default(builder.shape) && !reader.read("Shape", builder.shape))
	{
		// could not read shape
		return false;
	}
	if (builder.shape == Shape::Empty)
	{
		// read shape, but it is empty, so do nothing
		return true;
	}
	reader.read("Size", builder.size);
	reader.read("Static", builder.isStatic);
	if (builder.shape == Shape::Custom)
	{
		Ref<Mesh> mesh;
		reader.read("Mesh", mesh);
		builder.mesh = mesh;
	}
	else
	{
		builder.mesh = nullptr; // no mesh for non-custom shapes
	}
	collider = Collider::create(builder);
	return collider != nullptr; // return true if a collider was created
}
