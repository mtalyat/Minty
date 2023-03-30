#include "pch.h"
#include "M_RectF.h"
#include "M_Math.h"

namespace minty
{
	bool RectF::overlaps(RectF const& other) const
	{
		return left() < other.right() && right() > other.left() &&
			top() < other.bottom() && bottom() > other.top();
	}

	RectF RectF::overlap(RectF const& other) const
	{
		float xMin = math_clamp(other.x - x, 0.0f, width);
		float yMin = math_clamp(other.y - y, 0.0f, height);

		float xMax = math_clamp(other.x + other.width - x, 0.0f, width);
		float yMax = math_clamp(other.y + other.height - y, 0.0f, height);

		return RectF(xMin, yMin, xMax - xMin, yMax - yMin);
	}

	bool RectF::contains(PointF const& other) const
	{
		return other.x >= x && other.x < x + width && other.y >= y && other.y < y + height;
	}

	RectF RectF::bounds(float const left, float const right, float const top, float const bottom)
	{
		return RectF(left, top, right - left, bottom - top);
	}

	Rect RectF::floor(RectF const& rect)
	{
		return Rect(math_floorToInt(rect.x), math_floorToInt(rect.y), math_floorToInt(rect.width), math_floorToInt(rect.height));
	}

	Rect RectF::round(RectF const& rect)
	{
		return Rect(math_roundToInt(rect.x), math_roundToInt(rect.y), math_roundToInt(rect.width), math_roundToInt(rect.height));
	}

	Rect RectF::ceil(RectF const& rect)
	{
		return Rect(math_ceilToInt(rect.x), math_ceilToInt(rect.y), math_ceilToInt(rect.width), math_ceilToInt(rect.height));
	}
}
