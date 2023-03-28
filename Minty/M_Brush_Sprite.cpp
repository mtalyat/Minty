#include "pch.h"
#include "M_Brush_Sprite.h"

namespace minty
{
	SpriteBrush::SpriteBrush(Sprite const* const sprite, bool const absolute)
		: Brush(absolute)
		, sprite(sprite)
	{}

	SpriteBrush::~SpriteBrush()
	{
	}
	
	color_t SpriteBrush::getColor(int const x, int const y) const
	{
		// get position within sprite, return that color
		return sprite->getColor(x, y);
	}
}
