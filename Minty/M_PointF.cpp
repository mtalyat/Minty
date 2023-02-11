#include "pch.h"
#include "M_PointF.h"
#include "M_Point.h"
#include "M_Math.h"

namespace minty
{
    Point PointF::toPointF() const
    {
        return Point(math_floorToInt(x), math_floorToInt(y));
    }

    inline std::string const PointF::toString() const { return std::format("PointF({0}, {1})", x, y); }
}
