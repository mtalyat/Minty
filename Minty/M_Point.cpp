#include "pch.h"
#include "M_Point.h"
#include "M_PointF.h"

namespace minty
{
	inline minty::Point::Point(float const _x, float const _y)
		: x(math_floorToInt(_x)), y(math_floorToInt(_y)) {}

	PointF Point::toPointF() const
	{
		return PointF(x, y);
	}
}
