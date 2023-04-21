#pragma once

#include "M_Main.h"
#include "M_PointF.h"

namespace minty
{
	/// <summary>
	/// Holds local positioning data.
	/// </summary>
	struct MINTY_API Position
	{
		/// <summary>
		/// The X position.
		/// </summary>
		float x;
		/// <summary>
		/// The Y position.
		/// </summary>
		float y;

		/// <summary>
		/// Gets the X and Y position as a PointF.
		/// </summary>
		/// <returns>The X and Y position.</returns>
		inline PointF toPointF() const { return PointF(x, y); }
	};
}