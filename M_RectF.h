#pragma once

#include "M_Object.h"
#include "M_PointF.h"
#include "M_Point.h"
#include "M_Rect.h"

namespace minty
{
	struct RectF
		: public Object
	{
	public:
		float x, y, width, height;

	public:
		RectF()
			: x(0)
			, y(0)
			, width(0)
			, height(0)
		{}

		RectF(float const width, float const height)
			: x(0)
			, y(0)
			, width(width)
			, height(height)
		{}

		RectF(PointF const size)
			: x(0)
			, y(0)
			, width(size.x)
			, height(size.y)
		{}

		RectF(float const x, float const y, float const width, float const height)
			: x(x)
			, y(y)
			, width(width)
			, height(height)
		{}

		RectF(int const x, int const y, int const width, int const height)
			: x(static_cast<float>(x))
			, y(static_cast<float>(y))
			, width(static_cast<float>(width))
			, height(static_cast<float>(height))
		{}

		RectF(PointF const position, PointF const size)
			: x(position.x)
			, y(position.y)
			, width(size.x)
			, height(size.y)
		{}

		RectF(Point const position, Point const size)
			: x(static_cast<float>(position.x))
			, y(static_cast<float>(position.y))
			, width(static_cast<float>(size.x))
			, height(static_cast<float>(size.y))
		{}

		constexpr float left() const { return x; }
		constexpr float right() const { return x + width; }
		constexpr float top() const { return y; }
		constexpr float bottom() const { return y + height; }

		constexpr float area() const { return width * height; }

		inline PointF position() const { return PointF(x, y); }
		inline PointF size() const { return PointF(width, height); }

		/// <summary>
		/// Checks if this RectF overlaps with the given RectF.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		inline bool overlaps(RectF const& other);

		/// <summary>
		/// Returns the RectF that contains the area that this RectF and the given RectF overlap in.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		RectF overlap(RectF const& other) const;

		/// <summary>
		/// Checks if this RectF contains the given Point.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		inline bool contains(PointF const& other);

		static RectF bounds(float const left, float const right, float const top, float const bottom);

		static Rect floor(RectF const& rect);
		static Rect round(RectF const& rect);
		static Rect ceil(RectF const& rect);

		std::string const toString() const override;
	};
}