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
	: m_shape(info.shape), m_mesh(info.mesh), m_onEnter(nullptr), m_onStay(nullptr), m_onExit(nullptr), m_offset(info.offset), m_size(info.size), m_isStatic(info.isStatic), m_isTrigger(info.isTrigger)
{
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

void Minty::Serializer<Collider>::serialize(Writer &writer, Collider const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Collider>::deserialize(Reader &reader, Collider &value)
{
	MINTY_NOT_IMPLEMENTED();
	return false;
}