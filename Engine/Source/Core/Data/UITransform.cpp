#include "pch.hpp"
#include "UITransform.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Minty::UITransform::UITransform()
	: m_anchor(AnchorEnumFlags::TopLeft),
	  m_x(0.0f),
	  m_y(0.0f),
	  m_width(0.0f),
	  m_height(0.0f),
	  m_z(0.0f),
	  m_rotation(0.0f),
	  m_local(),
	  m_dirty(true)
{
}

Minty::UITransform::UITransform(Float const x, Float const y, Float const width, Float const height)
	: m_anchor(AnchorEnumFlags::TopLeft),
	  m_x(x),
	  m_y(y),
	  m_width(width),
	  m_height(height),
	  m_z(0.0f),
	  m_rotation(0.0f),
	  m_local(),
	  m_dirty(true)
{
}

Minty::UITransform::UITransform(Float const x, Float const y, Float const width, Float const height, Anchor const anchor)
	: m_anchor(anchor),
	  m_x(x),
	  m_y(y),
	  m_width(width),
	  m_height(height),
	  m_z(0.0f),
	  m_rotation(0.0f),
	  m_local(),
	  m_dirty(true)
{
}

Rect const &Minty::UITransform::get_local_rect() const
{
	if (m_dirty)
	{
		m_local.x = m_x;
		m_local.y = m_y;
		m_local.width = m_width;
		m_local.height = m_height;
		m_dirty = false;
	}
	return m_local;
}

Rect const &Minty::UITransform::get_global_rect() const
{
	// TODO: get actual global rect
	return get_local_rect();
}

void Minty::Serializer<UITransform>::serialize(Writer &writer, UITransform const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<UITransform>::deserialize(Reader &reader, UITransform &value)
{
	Bool modified = false;

	modified |= reader.read("Anchor", value.m_anchor);
	Bool readValue = reader.read("X", value.m_x);
	modified |= readValue;
	if (!readValue)
	{
		modified |= reader.read("Left", value.m_x);
	}
	readValue = reader.read("Y", value.m_y);
	modified |= readValue;
	if (!readValue)
	{
		modified |= reader.read("Top", value.m_y);
	}
	readValue = reader.read("Width", value.m_width);
	modified |= readValue;
	if (!readValue)
	{
		modified |= reader.read("Right", value.m_width);
	}
	readValue = reader.read("Height", value.m_height);
	modified |= readValue;
	if (!readValue)
	{
		modified |= reader.read("Bottom", value.m_height);
	}
	readValue = reader.read("Z", value.m_z);
	modified |= readValue;
	if (!readValue)
	{
		modified |= reader.read("Depth", value.m_z);
	}
	Float degrees = 0.0f;
	if (reader.read("Rotation", degrees))
	{
		value.m_rotation = Math::DEG2RAD * degrees;
		modified = true;
	}

	if (modified)
	{
		value.m_dirty = true;
	}
	return true;
}