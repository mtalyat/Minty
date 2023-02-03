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

		inline Point pos() const { return Point(x, y); }
	};
}