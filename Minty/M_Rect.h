#pragma once

#include "M_Saveable.h"
#include "M_Point.h"
#include <SDL.h>

namespace minty
{
	struct RectF;

	struct MINTY_API Rect
		: public Saveable
	{
	public:
		int x, y, width, height;

	public:
		Rect()
			: x(0)
			, y(0)
			, width(0)
			, height(0)
		{}

		Rect(int const width, int const height)
			: x(0)
			, y(0)
			, width(width)
			, height(height)
		{}

		Rect(Point const size)
			: x(0)
			, y(0)
			, width(size.x)
			, height(size.y)
		{}

		Rect(int const x, int const y, int const width, int const height)
			: x(x)
			, y(y)
			, width(width)
			, height(height)
		{}

		Rect(Point const position, Point const size)
			: x(position.x)
			, y(position.y)
			, width(size.x)
			, height(size.y)
		{}

		bool operator ==(Rect const& other) const
		{
			return x == other.x && y == other.y && width == other.width && height == other.height;
		}

		bool operator !=(Rect const& other) const
		{
			return x != other.x || y != other.y || width != other.width || height != other.height;
		}

		Rect operator +(Point const& point) const
		{
			return Rect(x + point.x, y + point.y, width, height);
		}

		Rect operator -(Point const& point) const
		{
			return Rect(x - point.x, y - point.y, width, height);
		}

		constexpr int left() const { return x; }
		constexpr int right() const { return x + width; }
		constexpr int top() const { return y; }
		constexpr int bottom() const { return y + height; }

		constexpr int area() const { return width * height; }

		inline Point position() const { return Point(x, y); }
		inline Point size() const { return Point(width, height); }
		inline Point center() const { return Point(x + width / 2, y + height / 2); }

		/// <summary>
		/// Checks if this Rect overlaps with the given Rect.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool overlaps(Rect const& other) const;

		/// <summary>
		/// Returns the Rect that contains the area that this Rect and the given Rect overlap in.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Rect overlap(Rect const& other) const;

		/// <summary>
		/// Checks if this Rect contains the given Point.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool contains(Point const& other) const;

		SDL_Rect toSDL() const;

		RectF toRectF() const;

		std::string const toString() const override { return std::format("Rect({0}, {1}, {2}, {3})", x, y, width, height); }

		void serialize(boost::property_tree::ptree& ptree) override;
		void deserialize(boost::property_tree::ptree const& ptree) override;

		static Rect bounds(int const left, int const right, int const top, int const bottom);

		static Rect round(RectF const& rect);
	};
}