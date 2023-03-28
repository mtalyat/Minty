#pragma once

#include "M_Brush.h"
#include "M_Sprite.h"

namespace minty
{
	class MINTY_API SpriteBrush
		: public Brush
	{
	public:
		Sprite const* const sprite;

	public:
		SpriteBrush(Sprite const* const sprite, bool const absolute = false);

		~SpriteBrush();

		color_t getColor(int const x, int const y) const override;
	};
}