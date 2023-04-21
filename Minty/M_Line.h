#pragma once

#include "M_Main.h"
#include "M_Point.h"
#include <vector>

namespace minty
{
	/// <summary>
	/// Generates a list of points from (x1, y1) to (x2, y2).
	/// </summary>
	/// <param name="x1">The starting column.</param>
	/// <param name="y1">The starting row.</param>
	/// <param name="x2">The ending column.</param>
	/// <param name="y2">The ending row.</param>
	/// <returns>A list of Points on a line between and including the given Points.</returns>
	MINTY_API std::vector<Point>* line_points(int const x1, int const y1, int const x2, int const y2);

	/// <summary>
	/// Finds the normalized amount to increment by to get from  (x1, y1) to (x2, y2).
	/// </summary>
	/// <param name="x1">The starting column.</param>
	/// <param name="y1">The starting row.</param>
	/// <param name="x2">The ending column.</param>
	/// <param name="y2">The ending row.</param>
	/// <param name="xinc">The amount to increment the X position by each iteration.</param>
	/// <param name="yinc">The amount to increment the Y position by each iteration.</param>
	/// <returns>The number of times to incrememnt to get from p1 to p2.</returns>
	MINTY_API int line_normalized(int const x1, int const y1, int const x2, int const y2, float& xinc, float& yinc);

	/// <summary>
	/// Finds the normalized amount to increment by to get from  (x1, y1) to (x2, y2).	
	/// </summary>
	/// <param name="x1">The starting column.</param>
	/// <param name="y1">The starting row.</param>
	/// <param name="x2">The ending column.</param>
	/// <param name="y2">The ending row.</param>
	/// <param name="xinc">The amount to increment the X position by each iteration.</param>
	/// <param name="yinc">The amount to increment the Y position by each iteration.</param>
	/// <returns>The number of times to incrememnt to get from p1 to p2.</returns>
	MINTY_API int line_normalized(float const x1, float const y1, float const x2, float const y2, float& xinc, float& yinc);
}