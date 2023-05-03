#pragma once

#include "M_Main.h"

namespace minty
{
	struct MINTY_API MouseMoveEvent
	{
		/// <summary>
		/// Previous position.
		/// </summary>
		int xPrev, yPrev;

		/// <summary>
		/// Current position.
		/// </summary>
		int x, y;
	};
}