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
	
	void Point::serialize(boost::property_tree::ptree& ptree)
	{
		ptree.put("x", x);
		ptree.put("y", y);
	}

	void Point::deserialize(boost::property_tree::ptree const& ptree)
	{
		x = ptree.get("x", 0);
		y = ptree.get("y", 0);
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
