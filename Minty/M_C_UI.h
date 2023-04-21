#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Holds data for a User Interface entity. Position is relative to the screen.
	/// </summary>
	struct MINTY_API UI
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
		/// The X anchor value. 0.0 is left, and 1.0 is right.
		/// </summary>
		float anchorX;
		/// <summary>
		/// The Y anchor value. 0.0 is top, and 1.0 is bottom.
		/// </summary>
		float anchorY;
	};
}