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
		float x, y;

		inline PointF toPointF() const { return PointF(x, y); }
	};
}