#include "pch.h"
#include "Bullet_ShapeCollider.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Mesh.h"
#include "Platform/Bullet/Bullet_Physics.h"

using namespace Minty;

Minty::Bullet_ShapeCollider::Bullet_ShapeCollider(ColliderBuilder const& builder)
	: Bullet_Collider(builder)
{
	MINTY_ASSERT(builder.shape != Shape::Empty, "ShapeCollider must have a non-empty shape.");
	MINTY_ASSERT(builder.shape != Shape::Custom, "ShapeCollider cannot have a custom shape. Use a MeshCollider instead.");
	MINTY_ASSERT(builder.size != Math::ZERO, "ShapeCollider size cannot be zero.");
	MINTY_ASSERT(builder.mesh == nullptr, "ShapeCollider cannot have custom data. Use a MeshCollider instead, or set to null.");

	// create the collision shape based on the builder
	btVector3 size = Bullet_Physics::to_bullet(builder.size);
	switch (builder.shape)
	{
	case Shape::Box:
		mp_shape = new btBoxShape(size);
		break;
	default:
		MINTY_ABORT("Unknown shape type.");
		break;
	}
}
