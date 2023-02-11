#pragma once

#include "M_Main.h"
#include "M_Point.h"
#include "M_PointF.h"

namespace minty
{
	/// <summary>
	/// Holds data regarding rendering to the screen.
	/// </summary>
	struct MINTY_API Renderable
	{
		float x, y;

		inline Point toPoint() const { return Point(x, y); }
		inline PointF toPointF() const { return PointF(x, y); }
	};
}