#include "pch.h"
#include "Bullet_Collider.h"
#include "Minty/Debug/Debug.h"
#include "Platform/Bullet/Bullet_Physics.h"

using namespace Minty;

Minty::Bullet_Collider::Bullet_Collider(ColliderBuilder const& builder)
	: Collider(builder)
	, mp_shape(nullptr)
	, mp_object(nullptr)
{
	btVector3 size = Bullet_Physics::to_bullet(builder.size);

	switch (builder.shape)
	{
	case Shape::Empty:
		break;
	case Shape::Box:
		mp_shape = new btBoxShape(size);
		break;
	default:
		MINTY_ABORT("Unknown shape type.");
		break;
	}
}

Minty::Bullet_Collider::~Bullet_Collider()
{
	delete mp_shape;
	delete mp_object;
}
