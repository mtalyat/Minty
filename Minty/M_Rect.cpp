#include "pch.h"
#include "M_Rect.h"
#include "M_RectF.h"

namespace minty
{
	inline bool minty::Rect::overlaps(Rect const& other)
	{
		return left() < other.right() && right() > other.left() &&
			top() < other.bottom() && bottom() > other.top();
	}

	inline Rect Rect::overlap(Rect const& other)
	{
		int xMin = math_clamp(other.x - x, 0, width);
		int yMin = math_clamp(other.y - y, 0, height);

		int xMax = math_clamp(other.x + other.width - x, 0, width);
		int yMax = math_clamp(other.y + other.height - y, 0, height);

		return Rect(xMin, yMin, xMax - xMin, yMax - yMin);
	}

	inline bool Rect::contains(Point const& other)
	{
		return other.x >= x && other.x < x + width && other.y >= y && other.y < y + height;
	}

	std::string const Rect::toString() const
	{
		return std::format("Rect({0}, {1}, {2}, {3})", x, y, width, height);
	}

	Rect Rect::bounds(int const left, int const right, int const top, int const bottom)
	{
		return Rect(left, top, right - left + 1, bottom - top + 1);
	}
	
	Rect Rect::round(RectF const& rect)
	{
		return Rect(math_roundToInt(rect.x), math_roundToInt(rect.y), math_roundToInt(rect.width), math_roundToInt(rect.height));
	}
}