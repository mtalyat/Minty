#include "pch.h"
#include "M_PointF.h"

namespace minty
{
	inline std::string const PointF::toString() const { return std::format("PointF({0}, {1})", x, y); }
}
