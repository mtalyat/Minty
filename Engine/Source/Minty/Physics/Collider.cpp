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
	: m_shape(info.shape), m_mesh(info.mesh), m_offset(info.offset), m_size(info.size), m_isStatic(info.isStatic)
{
}

void Minty::Collider::serialize(Writer &writer) const
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Collider::deserialize(Reader &reader)
{
	// read the shape
	reader.read("Shape", m_shape);
	if (m_shape == Shape::Empty)
	{
		m_size = Math::ZERO;
		m_mesh = nullptr;
		m_isStatic = false;
		return true; // no data to deserialize
	}
	reader.read("Offset", m_offset);
	reader.read("Size", m_size);
	if (m_shape == Shape::Custom)
	{
		// read the mesh if custom shape
		reader.read("Mesh", m_mesh);
	}
	else
	{
		m_mesh = nullptr; // no mesh for non-custom shapes
	}
	reader.read("Static", m_isStatic);
	return true;
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
