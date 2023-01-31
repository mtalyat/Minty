#include "pch.h"
#include "M_Hitbox.h"

namespace minty
{
	Hitbox::Hitbox(Rect const rect, Mask* const mask)
		: m_rect(rect)
		, mp_mask(mask)
	{}

	Hitbox::Hitbox(Point const offset, Point const size, Mask* const mask)
		: m_rect(offset, size)
		, mp_mask(mask)
	{}

	Hitbox::Hitbox(int const xOffset, int const yOffset, int const width, int const height, Mask* const mask)
		: m_rect(xOffset, yOffset, width, height)
		, mp_mask(mask)
	{}

	std::string const Hitbox::toString() const
	{
		return m_rect.toString();
	}
}