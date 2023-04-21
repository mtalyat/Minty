#pragma once

#include "M_Brush.h"

namespace minty
{
	/// <summary>
	/// A tool used to get a solid color when filling in or drawing on a Canvas.
	/// </summary>
	class MINTY_API SolidBrush
		: public Brush
	{
	public:
		// the color to draw
		color_t const color;

	public:
		/// <summary>
		/// Creates a new SolidBrush using the given color.
		/// </summary>
		/// <param name="color">The color to paint with.</param>
		/// <param name="absolute">If true, all strokes will have their pattern relative to the origin.</param>
		SolidBrush(color_t const color, bool const absolute = false);

		~SolidBrush();

		color_t getColor(int const x, int const y) const override;
	};
}