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
		/// The positional data.
		/// </summary>
		float x, y;

		/// <summary>
		/// The anchor data. Determines which point on the screen the positional data is relative to.
		/// 0, 0 is top left.
		/// </summary>
		float anchorX, anchorY;

		/// <summary>
		/// The pivot data. Determines which point on the entity the positional data is relative to.
		/// 0, 0 is top left.
		/// </summary>
		float pivotX, pivotY;
	};
}