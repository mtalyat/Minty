#pragma once

#include "M_Brush.h"
#include "M_Sprite.h"

namespace minty
{
	/// <summary>
	/// A tool used to get a color from a Sprite when filling in or drawing on a Canvas.
	/// </summary>
	class MINTY_API SpriteBrush
		: public Brush
	{
	public:
		// the sprite to pull colors from
		Sprite const* const sprite;

	public:
		/// <summary>
		/// Creates a new SpriteBrush using the given Sprite.
		/// </summary>
		/// <param name="sprite">The Sprite to pull colors from.</param>
		/// <param name="absolute">If true, all strokes will have their pattern relative to the origin.</param>
		SpriteBrush(Sprite const* const sprite, bool const absolute = false);

		~SpriteBrush();

		color_t getColor(int const x, int const y) const override;
	};
}