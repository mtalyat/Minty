#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_Mask.h"

namespace minty
{
	/// <summary>
	/// Holds specific collider data for an entity.
	/// </summary>
	class MINTY_API Hitbox
		: public Object
	{
	private:
		Rect m_rect;

		Mask* mp_mask;

	public:
		Hitbox(Rect const rect, Mask* const mask = nullptr);
		Hitbox(Point const offset, Point const size, Mask* const mask = nullptr);
		Hitbox(int const xOffset, int const yOffset, int const width, int const height, Mask* const mask = nullptr);

		inline Rect const& rect() const { return m_rect; }
		inline Mask* const mask() const { return mp_mask; }

		inline void setMask(Mask* const mask) { mp_mask = mask; }

		std::string const toString() const override;
	};
}