#include "pch.h"
#include "UITransform.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::UITransform::UITransform()
	: m_anchorMode(AnchorMode::TopLeft), m_x(0.0f), m_width(0.0f), m_height(0.0f), m_z(0.0f), m_rotation(0.0f), m_globalDepth(0.0f), m_globalRect()
{
}

void Minty::UITransform::update(Rect const &parentRect, Float const parentDepth, Float const parentRotation)
{
	// mask the anchor mode to get the vertical and horizontal modes
	// the mask is needed so they are independent of one another
	AnchorMode horizontal = m_anchorMode & AnchorMode::Horizontal;
	AnchorMode vertical = m_anchorMode & AnchorMode::Vertical;

	// update horizontal
	if ((horizontal & AnchorMode::Left) == horizontal)
	{
		m_globalRect.x = parentRect.x + m_x;
		m_globalRect.width = m_width;
	}
	else if ((horizontal & AnchorMode::Center) == horizontal)
	{
		m_globalRect.x = parentRect.x + m_x + (parentRect.width * 0.5f);
		m_globalRect.width = m_width;
	}
	else if ((horizontal & AnchorMode::Right) == horizontal)
	{
		m_globalRect.x = parentRect.x + m_x + parentRect.width;
		m_globalRect.width = m_width;
	}
	else
	{
		// stretch
		m_globalRect.x = parentRect.x + m_x;
		m_globalRect.width = parentRect.width - m_width - m_globalRect.x;
	}

	// update vertical
	if ((vertical & AnchorMode::Top) == vertical)
	{
		m_globalRect.y = parentRect.y + m_y;
		m_globalRect.height = m_height;
	}
	else if ((vertical & AnchorMode::Middle) == vertical)
	{
		m_globalRect.y = parentRect.y + m_y + (parentRect.height * 0.5f);
		m_globalRect.height = m_height;
	}
	else if ((vertical & AnchorMode::Bottom) == vertical)
	{
		m_globalRect.y = parentRect.y + m_y + parentRect.height;
		m_globalRect.height = m_height;
	}
	else
	{
		// stretch
		m_globalRect.y = parentRect.y + m_y;
		m_globalRect.height = parentRect.height - m_height - m_globalRect.y;
	}

	// update the global depth, rotation
	m_globalDepth = parentDepth + m_z;
	m_globalRotation = parentRotation + m_rotation;
}

void Minty::Serializer<UITransform>::serialize(Writer &writer, UITransform const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<UITransform>::deserialize(Reader &reader, UITransform &value)
{
	reader.read("AnchorMode", value.m_anchorMode);
	if (!reader.read("X", value.m_x))
	{
		reader.read("Left", value.m_x);
	}
	if (!reader.read("Y", value.m_y))
	{
		reader.read("Top", value.m_y);
	}
	if (!reader.read("Width", value.m_width))
	{
		reader.read("Right", value.m_width);
	}
	if (!reader.read("Height", value.m_height))
	{
		reader.read("Bottom", value.m_height);
	}
	if (!reader.read("Z", value.m_z))
	{
		reader.read("Depth", value.m_z);
	}
	Float degrees = 0.0f;
	if (reader.read("Rotation", degrees))
	{
		value.m_rotation = Math::DEG2RAD * degrees;
	}
	return true;
}