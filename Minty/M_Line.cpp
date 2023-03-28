#include "pch.h"
#include "M_Line.h"

namespace minty
{
	std::vector<Point>* line_points(int const x1, int const y1, int const x2, int const y2)
	{
		std::vector<Point>* points = new std::vector<Point>();

		float xinc, yinc;

		int dmax = line_normalized(x1, y1, x2, y2, xinc, yinc);

		// keep track of x and y we are at on the line
		float x = static_cast<float>(x1);
		float y = static_cast<float>(y1);

		// iterate from 1 to 2
		// add each point as we go
		for (int i = 0; i <= dmax; i++)
		{
			// add point
			points->push_back(Point(math_floorToInt(x), math_floorToInt(y)));

			// move to next point
			x += xinc;
			y += yinc;
		}

		return points;
	}

	int line_normalized(int const x1, int const y1, int const x2, int const y2, float& xinc, float& yinc)
	{
		// find difference between two points
		int dx = x2 - x1;
		int dy = y2 - y1;

		// find max of two differences
		// also amount of times to increment
		int dmax = math_abs(math_abs(dx) > math_abs(dy) ? dx : dy);

		float dmaxf = static_cast<float>(dmax);

		// determine increment amount
		xinc = dmaxf == 0.0f ? 0.0f : static_cast<float>(dx) / dmaxf;
		yinc = dmaxf == 0.0f ? 0.0f : static_cast<float>(dy) / dmaxf;

		// dmax is the number of times to iterate
		return dmax;
	}
}