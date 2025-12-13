#include "pch.h"
#include "Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_Collider.h"
#endif

using namespace Minty;

Minty::Collider::Collider(ColliderInfo const &info)
	: m_shape(info.shape), m_mesh(info.mesh)
{
}

void Minty::Collider::serialize(Writer &writer) const
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Collider::deserialize(Reader &reader)
{
	MINTY_NOT_IMPLEMENTED();
	return false;
}

Shared<Collider> Minty::Collider::create(ColliderInfo const &info)
{
	// create a shape collider or a mesh collider based on the shape type
	switch (info.shape)
	{
	case Shape::Empty:
		// no collider
		return Shared<Collider>();
	default:
#if defined(MINTY_BULLET)
		return Shared<Bullet_Collider>::create(info);
#else
		return Shared<Collider>();
#endif
	}
}

Shared<Collider> Minty::Collider::create()
{
	ColliderInfo info{};
	return create(info);
}
