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
	
	Point Point::polarToCartesian(Point& const polar)
	{
		return Point(math_cos(polar.x) * polar.y, math_sin(polar.x) * polar.y);
	}
	
	Point Point::cartesianToPolar(Point& const cartesian)
	{
		return Point(math_angle(cartesian.x, cartesian.y), math_distance(cartesian.x, cartesian.y));
	}
}
