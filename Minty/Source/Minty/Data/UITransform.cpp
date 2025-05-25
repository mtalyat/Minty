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
	writer.write("anchorMode", m_anchorMode);
	writer.write("x", x);
	writer.write("y", y);
	writer.write("z", z);
	writer.write("width", width);
	writer.write("height", height);
}

Bool Minty::UITransform::deserialize(Reader& reader)
{
	reader.read("anchorMode", m_anchorMode);
	if (!reader.read("x", x))
	{
		reader.read("left", x);
	}
	if (!reader.read("y", y))
	{
		reader.read("top", y);
	}
	if (!reader.read("z", z))
	{
		reader.read("depth", z);
	}
	if (!reader.read("width", width))
	{
		reader.read("right", width);
	}
	if (!reader.read("height", height))
	{
		reader.read("bottom", height);
	}
	return true;
}
