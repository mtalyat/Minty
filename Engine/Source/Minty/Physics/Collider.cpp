#include "pch.h"
#include "Collider.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_ShapeCollider.h"
#include "Platform/Bullet/Bullet_MeshCollider.h"
#endif

using namespace Minty;

Owner<Collider> Minty::Collider::create(ColliderBuilder const& builder)
{
	// create a shape collider or a mesh collider based on the shape type
	switch (builder.shape)
	{
	case Shape::Empty:
		// no collider
		return Owner<Collider>();
	case Shape::Custom:
		// custom mesh collider
#if defined(MINTY_BULLET)
		return Owner<Bullet_MeshCollider>(builder);
#else
		return Owner<Collider>();
#endif
	default:
		// simple shape collider
#if defined(MINTY_BULLET)
		return Owner<Bullet_ShapeCollider>(builder);
#else
		return Owner<Collider>();
#endif
	}
}

void Minty::Collider::serialize(Writer& writer) const
{
	writer.write("Shape", m_shape);
	if (m_shape == Shape::Empty)
	{
		return; // no data to serialize
	}
	writer.write("Size", m_size);
	if (m_shape == Shape::Custom && m_mesh != nullptr)
	{
		writer.write("Mesh", m_mesh);
	}
	else
	{
		writer.write("Mesh", Ref<Mesh>());
	}
	writer.write("Static", m_isStatic);
}

Bool Minty::Collider::deserialize(Reader& reader)
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
