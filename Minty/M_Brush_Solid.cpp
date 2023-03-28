#include "pch.h"
#include "M_Brush_Solid.h"

namespace minty
{
	SolidBrush::SolidBrush(color_t const color, bool const absolute)
		: Brush(absolute)
		, color(color)
	{}
	
	SolidBrush::~SolidBrush()
	{
	}
	
	color_t SolidBrush::getColor(int const x, int const y) const
	{
		return color;
	}
}
