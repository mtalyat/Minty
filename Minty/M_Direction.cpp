#include "pch.h"
#include "M_Direction.h"

namespace minty
{
	Point direction_toPoint(int const dir)
	{
		switch (dir)
		{
		case 1:
			return Point(1, 0);
		case 2:
			return Point(1, -1);
		case 3:
			return Point(0, -1);
		case 4:
			return Point(-1, -1);
		case 5:
			return Point(-1, 0);
		case 6:
			return Point(-1, 1);
		case 7:
			return Point(0, 1);
		case 8:
			return Point(1, 1);
		default:
			return Point();
		}
	}
}
