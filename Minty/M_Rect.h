#pragma once

#include "M_Saveable.h"
#include "M_Point.h"
#include <SDL.h>

namespace minty
{
	struct RectF;

	/// <summary>
	/// Holds an X and Y coordinate, as well as a width and height for a rectangle in space.
	/// </summary>
	struct MINTY_API Rect
		: public Saveable
	{
	public:
		/// <summary>
		/// The column position of the Rectangle.
		/// </summary>
		int x;
		/// <summary>
		/// The row position of the Rectangle.
		/// </summary>
		int y;
		/// <summary>
		/// The width of the Rectangle.
		/// </summary>
		int width;
		/// <summary>
		/// The height of the Rectangle.
		/// </summary>
		int height;

	public:
		/// <summary>
		/// Creates an empty Rectangle.
		/// </summary>
		Rect()
			: x(0)
			, y(0)
			, width(0)
			, height(0)
		{}

		/// <summary>
		/// Creates a new Rectangle using the given width and height.
		/// </summary>
		/// <param name="width">The width of the Rectangle.</param>
		/// <param name="height">The height of the Rectangle.</param>
		Rect(int const width, int const height)
			: x(0)
			, y(0)
			, width(width)
			, height(height)
		{}

		/// <summary>
		/// Creates a new Rectangle using the given Point size.
		/// </summary>
		/// <param name="size">The size of the Rectangle.</param>
		Rect(Point const size)
			: x(0)
			, y(0)
			, width(size.x)
			, height(size.y)
		{}

		/// <summary>
		/// Creates a new Rectangle using the given X and Y position, width and height.
		/// </summary>
		/// <param name="x">The column of the Rectangle.</param>
		/// <param name="y">The row of the Rectangle.</param>
		/// <param name="width">The width of the Rectangle.</param>
		/// <param name="height">The height of the Rectangle.</param>
		Rect(int const x, int const y, int const width, int const height)
			: x(x)
			, y(y)
			, width(width)
			, height(height)
		{}

		/// <summary>
		/// Creates a new Rectangle using the given position and size.
		/// </summary>
		/// <param name="position">The position of the Rectangle.</param>
		/// <param name="size">The size of the Rectangle.</param>
		Rect(Point const position, Point const size)
			: x(position.x)
			, y(position.y)
			, width(size.x)
			, height(size.y)
		{}

		// equals operator
		bool operator ==(Rect const& other) const
		{
			return x == other.x && y == other.y && width == other.width && height == other.height;
		}

		// not equals operator
		bool operator !=(Rect const& other) const
		{
			return x != other.x || y != other.y || width != other.width || height != other.height;
		}

		// add operator
		Rect operator +(Point const& point) const
		{
			return Rect(x + point.x, y + point.y, width, height);
		}

		// subtract operator
		Rect operator -(Point const& point) const
		{
			return Rect(x - point.x, y - point.y, width, height);
		}

		/// <summary>
		/// Gets the leftmost column of the Rectangle.
		/// </summary>
		/// <returns>The minimum X position.</returns>
		constexpr int left() const { return x; }
		/// <summary>
		/// Gets the rightmost column of the Rectangle.
		/// </summary>
		/// <returns>The maximum X position.</returns>
		constexpr int right() const { return x + width; }
		/// <summary>
		/// Gets the topmost row of the Rectangle.
		/// </summary>
		/// <returns>The minimum Y position.</returns>
		constexpr int top() const { return y; }
		/// <summary>
		/// Gets the bottommost row of the Rectangle.
		/// </summary>
		/// <returns>The maximum Y position.</returns>
		constexpr int bottom() const { return y + height; }

		/// <summary>
		/// Gets the area of the Rectangle.
		/// </summary>
		/// <returns>The width * height.</returns>
		constexpr int area() const { return width * height; }

		/// <summary>
		/// Gets the position of the Rectangle, as a Point.
		/// </summary>
		/// <returns>The X and Y position.</returns>
		inline Point position() const { return Point(x, y); }
		/// <summary>
		/// Gets the size of the Rectangle, as a Point.
		/// </summary>
		/// <returns>The size.</returns>
		inline Point size() const { return Point(width, height); }
		/// <summary>
		/// Gets the center position of the Rectangle, as a Point.
		/// </summary>
		/// <returns>The center position.</returns>
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

		/// <summary>
		/// Converts this Rect to an SDL_Rect.
		/// </summary>
		/// <returns>An SDL_Rect with this Rect's values..</returns>
		SDL_Rect toSDL() const;

		/// <summary>
		/// Converts this Rect to a RectF.
		/// </summary>
		/// <returns>A RectF with this Rect's values.</returns>
		RectF toRectF() const;

		std::string const toString() const override { return std::format("Rect({0}, {1}, {2}, {3})", x, y, width, height); }

		void serialize(boost::property_tree::ptree& ptree) override;
		void deserialize(boost::property_tree::ptree const& ptree) override;

		/// <summary>
		/// Creates a Rect using the given bounds of each size of the Rect.
		/// </summary>
		/// <param name="left">The minimum X.</param>
		/// <param name="right">The maximum X.</param>
		/// <param name="top">The minimum Y.</param>
		/// <param name="bottom">The maximum Y.</param>
		/// <returns></returns>
		static Rect bounds(int const left, int const right, int const top, int const bottom);

		/// <summary>
		/// Rounds the given RectF into a Rect.
		/// </summary>
		/// <param name="rect">The RectF to round.</param>
		/// <returns>A Rect, with the given rect's values, rounded.</returns>
		static Rect round(RectF const& rect);
	};
}