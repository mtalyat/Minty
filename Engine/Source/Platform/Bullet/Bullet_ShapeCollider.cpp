#include "pch.h"
#include "Bullet_ShapeCollider.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Mesh.h"
#include "Platform/Bullet/Bullet_Physics.h"
#include "Minty/Physics/ColliderInfo.h"

using namespace Minty;

Minty::Bullet_ShapeCollider::Bullet_ShapeCollider(ColliderInfo const& info)
	: Bullet_Collider(info)
{
	MINTY_ASSERT(info.shape != Shape::Empty, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.shape != Shape::Custom, ErrorCode::Argument_InvalidValue);
	MINTY_ASSERT(info.size != Math::ZERO, ErrorCode::Argument_ExpectedNonZero);
	MINTY_ASSERT(info.mesh == nullptr, ErrorCode::Argument_ExpectedNull);

	// create the collision shape based on the info
	btVector3 size = Bullet_Physics::to_bullet(info.size * 0.5f); // half size since Bullet uses half extents for box shapes
	switch (info.shape)
	{
	case Shape::Box:
		mp_shape = new btBoxShape(size);
		break;
	default:
		MINTY_NOT_IMPLEMENTED();
	}
}
