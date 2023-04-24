#include "pch.h"
#include "M_PointF.h"
#include "M_Point.h"
#include "M_Math.h"

namespace minty
{
    Point PointF::toPoint() const
    {
        return Point(math_floorToInt(x), math_floorToInt(y));
    }
    
    void PointF::serialize(boost::property_tree::ptree& ptree)
    {
        ptree.put("x", x);
        ptree.put("y", y);
    }

    void PointF::deserialize(boost::property_tree::ptree const& ptree)
    {
        x = ptree.get("x", 0.0f);
        y = ptree.get("y", 0.0f);
    }

    PointF PointF::polarToCartesian(PointF& const polar)
    {
        return PointF(math_cos(polar.x) * polar.y, math_sin(polar.x) * polar.y);
    }

    PointF PointF::cartesianToPolar(PointF& const cartesian)
    {
        return PointF(math_angle(cartesian.x, cartesian.y), math_distance(cartesian.x, cartesian.y));
    }
}
