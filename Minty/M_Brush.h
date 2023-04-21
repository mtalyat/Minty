#pragma once

#include "M_Object.h"
#include "M_Color.h"

namespace minty
{
	/// <summary>
	/// A generic tool used to get colors when filling in or drawing on a Canvas.
	/// </summary>
	class MINTY_API Brush
		: public Object
	{
	private:
		// is the position of this brush absolute, or relative?
		bool m_absolute;

	public:
		/// <summary>
		/// Creates a new Brush.
		/// </summary>
		/// <param name="absolute">If true, all strokes will have their pattern relative to the origin.</param>
		Brush(bool const absolute = false);

		virtual ~Brush();

		/// <summary>
		/// Gets if this Brush is absolute or relative.
		/// </summary>
		/// <returns>True if absolute, false if relative.</returns>
		constexpr bool isAbsolute() const { return m_absolute; }

		/// <summary>
		/// Gets the Color this Brush would paint at the given base (starting) position, and the actual position.
		/// </summary>
		/// <param name="baseX">The stroke starting X position.</param>
		/// <param name="baseY">The stroke starting Y position.</param>
		/// <param name="x">The current X position.</param>
		/// <param name="y">The current Y position.</param>
		/// <returns>The color at that position.</returns>
		color_t getColor(int const baseX, int const baseY, int const x, int const y) const;

		/// <summary>
		/// Gets the Color this Brush would paint at the given absolute position.
		/// </summary>
		/// <param name="x">The current X position.</param>
		/// <param name="y">The current Y position.</param>
		/// <returns>The color at that position.</returns>
		virtual color_t getColor(int const x, int const y) const = 0;
	};
}