#include "pch.h"
#include "M_Direction.h"
#include "M_Math.h"

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

	std::string direction_toString(int const dir)
	{
		switch (dir)
		{
		case 1:
			return "Right";
		case 2:
			return "UpRight";
		case 3:
			return "Up";
		case 4:
			return "UpLeft";
		case 5:
			return "Left";
		case 6:
			return "DownLeft";
		case 7:
			return "Down";
		case 8:
			return "DownRight";
		default:
			return "";
		}
	}

	Direction direction_getCardinalDirection(float const x, float const y)
	{
		if (math_abs(y) > math_abs(x))
		{
			if (y < 0.0f)
			{
				return Direction::Up;
			}
			else
			{
				return Direction::Down;
			}
		}
		else
		{
			if (x < 0.0f)
			{
				return Direction::Left;
			}
			else if (x > 0.0f)
			{
				return Direction::Right;
			}
			else
			{
				return Direction::None;
			}
		}
	}
}
