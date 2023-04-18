#include "pch.h"
#include "M_Rect.h"
#include "M_RectF.h"

namespace minty
{
	bool Rect::overlaps(Rect const& other) const
	{
		return left() < other.right() && right() > other.left() &&
			top() < other.bottom() && bottom() > other.top();
	}

	Rect Rect::overlap(Rect const& other) const
	{
		int xMin = math_clamp(other.x - x, 0, width);
		int yMin = math_clamp(other.y - y, 0, height);

		int xMax = math_clamp(other.x + other.width - x, 0, width);
		int yMax = math_clamp(other.y + other.height - y, 0, height);

		return Rect(xMin, yMin, xMax - xMin, yMax - yMin);
	}

	bool Rect::contains(Point const& other) const
	{
		return other.x >= x && other.x < x + width && other.y >= y && other.y < y + height;
	}

	SDL_Rect Rect::toSDL() const
	{
		return SDL_Rect{ x, y, width, height };
	}

	RectF Rect::toRectF() const
	{
		return RectF(x, y, width, height);
	}

	void Rect::serialize(boost::property_tree::ptree& ptree)
	{
		ptree.put("x", x);
		ptree.put("y", y);
		ptree.get("w", width);
		ptree.get("h", height);
	}

	void Rect::deserialize(const boost::property_tree::ptree& ptree)
	{
		x = ptree.get("x", 0);
		y = ptree.get("y", 0);
		width = ptree.get("w", 0);
		height = ptree.get("h", 0);
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