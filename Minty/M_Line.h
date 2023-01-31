#pragma once

#include "M_Main.h"
#include "M_Point.h"
#include <vector>

namespace minty
{
	/// <summary>
	/// Generates a list of points from (x1, y1) to (x2, y2).
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <returns></returns>
	MINTY_API std::vector<Point>* line_points(int const x1, int const y1, int const x2, int const y2);

	/// <summary>
	/// Finds the normalized amount to increment by to get from  (x1, y1) to (x2, y2).
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <param name="xinc"></param>
	/// <param name="yinc"></param>
	/// <returns>The number of times to incrememnt to get from p1 to p2.</returns>
	MINTY_API int line_normalized(int const x1, int const y1, int const x2, int const y2, float& xinc, float& yinc);
}