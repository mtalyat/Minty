#pragma once

#include "M_Object.h"
#include "M_Color.h"
#include "M_Sprite.h"
#include "M_Brush.h"
#include <SDL.h>
#include <vector>

namespace minty
{
	/// <summary>
	/// A Canvas holds data to allow for easy modification of a Sprite/image, particularly with drawing on them.
	/// </summary>
	class MINTY_API Canvas
		: public Object
	{
	public:
		int const width;
		int const height;

	private:
		color_t* mp_pixels;
		Sprite* const mp_sprite;

	public:
		Canvas(int const width, int const height, SDL_Renderer* const renderer);

		~Canvas();

		void lock();

		void unlock();

		constexpr bool isLocked() const { return mp_pixels != nullptr; }

		inline void set(int const x, int const y, color_t const color);

		void set_s(int const x, int const y, color_t const color);

		constexpr color_t get(int const x, int const y) const;

		constexpr color_t get_s(int const x, int const y) const;

		constexpr bool contains(int const x, int const y) const;

#pragma region Drawing

		void draw(int const x, int const y, Brush const& brush);

		/// <summary>
		/// Draws a line from (x1, y1) to (x2, y2), using the given Brush and brush width.
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <param name="brush"></param>
		void drawLine(int const x1, int const y1, int const x2, int const y2, Brush const& brush);

		void drawRect(int const x, int const y, int const width, int const height, Brush const& brush);

		void drawCircle(int const xm, int const ym, int const radius, Brush const& brush);

		void drawSprite(int const x, int const y, Sprite const* const sprite);

#pragma endregion

#pragma region Filling

		void fillRect(int const x, int const y, int const width, int const height, Brush const& brush);

		void fillCircle(int const xm, int const ym, int const radius, Brush const& brush);

		void fillSlices(int const xm, int const ym, int const radius, std::vector<Sprite*> const& sprites, float offset = 0.0f);

#pragma endregion

#pragma region Clearing

		void clear(color_t const color = 0);

#pragma endregion

		Sprite* getSprite() const { return mp_sprite; }
	};
}