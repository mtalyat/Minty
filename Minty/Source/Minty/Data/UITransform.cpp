#include "pch.h"
#include "UITransform.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::UITransform::update_global_rect(Rect const& parentRect)
{
	// mask the anchor mode to get the vertical and horizontal modes
	// the mask is needed so they are independent of one another
	AnchorMode horizontal = m_anchorMode & AnchorMode::HorizontalMask;
	AnchorMode vertical = m_anchorMode & AnchorMode::VerticalMask;

	// update horizontal
	if ((horizontal & AnchorMode::Left) == horizontal)
	{
		m_globalRect.x = parentRect.x + x;
		m_globalRect.width = width;
	}
	else if ((horizontal & AnchorMode::Center) == horizontal)
	{
		m_globalRect.x = parentRect.x + x + (parentRect.width * 0.5f);
		m_globalRect.width = width;
	}
	else if ((horizontal & AnchorMode::Right) == horizontal)
	{
		m_globalRect.x = parentRect.x + x + parentRect.width;
		m_globalRect.width = width;
	}
	else
	{
		// stretch
		m_globalRect.x = parentRect.x + x;
		m_globalRect.width = parentRect.width - width - m_globalRect.x;
	}

	// update vertical
	if ((vertical & AnchorMode::Top) == vertical)
	{
		m_globalRect.y = parentRect.y + y;
		m_globalRect.height = height;
	}
	else if ((vertical & AnchorMode::Middle) == vertical)
	{
		m_globalRect.y = parentRect.y + y + (parentRect.height * 0.5f);
		m_globalRect.height = height;
	}
	else if ((vertical & AnchorMode::Bottom) == vertical)
	{
		m_globalRect.y = parentRect.y + y + parentRect.height;
		m_globalRect.height = height;
	}
	else
	{
		// stretch
		m_globalRect.y = parentRect.y + y;
		m_globalRect.height = parentRect.height - height - m_globalRect.y;
	}
}

void Minty::UITransform::serialize(Writer& writer) const
{
	writer.write("AnchorMode", m_anchorMode);
	writer.write("X", x);
	writer.write("Y", y);
	writer.write("Z", z);
	writer.write("Width", width);
	writer.write("Height", height);
}

Bool Minty::UITransform::deserialize(Reader& reader)
{
	reader.read("AnchorMode", m_anchorMode);
	if (!reader.read("X", x))
	{
		reader.read("Left", x);
	}
	if (!reader.read("Y", y))
	{
		reader.read("Top", y);
	}
	if (!reader.read("Z", z))
	{
		reader.read("Depth", z);
	}
	z = Math::clamp(z, 0.0f, 1.0f); // ensure depth is between 0 and 1
	if (!reader.read("Width", width))
	{
		reader.read("Right", width);
	}
	if (!reader.read("Height", height))
	{
		reader.read("Bottom", height);
	}
	return true;
}
