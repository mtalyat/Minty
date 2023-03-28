#pragma once

#include "M_Brush.h"

namespace minty
{
	class MINTY_API SolidBrush
		: public Brush
	{
	public:
		color_t const color;

	public:
		SolidBrush(color_t const color, bool const absolute = false);

		~SolidBrush();

		color_t getColor(int const x, int const y) const override;
	};
}