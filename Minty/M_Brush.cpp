#include "pch.h"
#include "M_Brush.h"

namespace minty
{
	Brush::Brush(bool const absolute)
		: m_absolute(absolute)
	{
	}
	
	Brush::~Brush()
	{
	}
	
	color_t Brush::getColor(int const baseX, int const baseY, int const x, int const y) const
	{
		if (m_absolute)
		{
			// absolute
			return getColor(x, y);
		}
		else
		{
			// relative
			return getColor(x - baseX, y - baseY);
		}
	}
}
