#include "pch.h"
#include "Bullet_ShapeCollider.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Mesh.h"
#include "Platform/Bullet/Bullet_Physics.h"

using namespace Minty;

Minty::Bullet_ShapeCollider::Bullet_ShapeCollider(ColliderInfo const& info)
	: Bullet_Collider(info)
{
	MINTY_ASSERT(info.shape != Shape::Empty, "ShapeCollider must have a non-empty shape.");
	MINTY_ASSERT(info.shape != Shape::Custom, "ShapeCollider cannot have a custom shape. Use a MeshCollider instead.");
	MINTY_ASSERT(info.size != Math::ZERO, "ShapeCollider size cannot be zero.");
	MINTY_ASSERT(info.mesh == nullptr, "ShapeCollider cannot have custom data. Use a MeshCollider instead, or set to null.");

	// create the collision shape based on the info
	btVector3 size = Bullet_Physics::to_bullet(info.size * 0.5f); // half size since Bullet uses half extents for box shapes
	switch (info.shape)
	{
	case Shape::Box:
		mp_shape = new btBoxShape(size);
		break;
	default:
		MINTY_ABORT("Unknown shape type.");
		break;
	}
}
