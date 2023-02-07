#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "M_Color.h"
#include <SDL.h>

namespace minty
{
	/// <summary>
	/// Holds a surface and texture, that can be rendered to the screen.
	/// </summary>
	class MINTY_API Sprite :
		public Object
	{
	public:
		int const width;
		int const height;
	private:
		Point m_offset;
		SDL_Surface* mp_surface;
		SDL_Texture* mp_texture;

	public:
		Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer);

		Sprite(SDL_Texture* const texture, int const w, int const h);

		Sprite(SDL_Surface* const surface, SDL_Texture* const texture);

		~Sprite();

		constexpr int size() const { return width * height; }
		inline Rect rect() const { return Rect(0, 0, width, height); }
		void setPivot(PointF const& pivot) { m_offset = Point(math_floorToInt(-pivot.x * static_cast<float>(width)), math_floorToInt(-pivot.y * static_cast<float>(height))); }
		inline Point offset() const { return m_offset; }
		inline SDL_Surface* surface() const { return mp_surface; }
		inline SDL_Texture* texture() const { return mp_texture; }

		/// <summary>
		/// Gets the color using the relative positions of the given X and Y positions.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		Color getColor(int const x, int const y);

		/// <summary>
		/// Gets the pixel at the given X and Y positions.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		Color at(int const x, int const y);

		Sprite* slice(Rect const& rect, SDL_Renderer* const renderer) const;
	};
}

