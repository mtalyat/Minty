#pragma once

#include "M_Object.h"
#include "M_Color.h"

namespace minty
{
	/// <summary>
	/// A Brush provides a way to get colors when drawing.
	/// </summary>
	class MINTY_API Brush
		: public Object
	{
	private:
		bool m_absolute;

	public:
		Brush(bool const absolute = false);

		virtual ~Brush();

		constexpr bool isAbsolute() const { return m_absolute; }

		color_t getColor(int const baseX, int const baseY, int const x, int const y) const;

		virtual color_t getColor(int const x, int const y) const = 0;
	};
}