#pragma once

#include "M_Main.h"
#include "M_Point.h"

namespace minty
{
	/// <summary>
	/// Holds data regarding a mouse click on the screen.
	/// </summary>
	struct MINTY_API Click
	{
		/// <summary>
		/// The index of the mouse button that was clicked.
		/// </summary>
		unsigned char button;

		/// <summary>
		/// The number of successive clicks.
		/// </summary>
		unsigned char clicks;

		/// <summary>
		/// The screen position of the click.
		/// </summary>
		int x, y;

		/// <summary>
		/// Gets the screen position of the click as a Point.
		/// </summary>
		/// <returns>x and y inside of a Point.</returns>
		inline Point toPoint() const { return Point(x, y); }
	};
}