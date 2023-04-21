#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "M_Color.h"
#include "M_Mask.h"
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
		/// <summary>
		/// The width of the Sprite, in pixels.
		/// </summary>
		int const width;
		/// <summary>
		/// The height of the Sprite, in pixels.
		/// </summary>
		int const height;
	private:
		// the offset of the pivot
		PointF m_offset;
		// the surface to render
		SDL_Surface* mp_surface;
		// the texture to render
		SDL_Texture* mp_texture;
		// the assiciated mask
		Mask* mp_mask;

	public:
		/// <summary>
		/// Creates a new Sprite using the given Surface and Renderer.
		/// </summary>
		/// <param name="surface">The Surface to create a Texture from.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer);

		/// <summary>
		/// Creates a new Texture using the given Texture, width and height.
		/// </summary>
		/// <param name="texture">The Texture to be rendererd to the screen.</param>
		/// <param name="w">The width of the Texture, in pixels.</param>
		/// <param name="h">The height of the Texture, in pixels.</param>
		Sprite(SDL_Texture* const texture, int const w, int const h);

		/// <summary>
		/// Creates a new Sprite using the given Surface and Texture.
		/// </summary>
		/// <param name="surface">The Surface associated with the Texture.</param>
		/// <param name="texture">The Texture to be rendererd to the screen.</param>
		Sprite(SDL_Surface* const surface, SDL_Texture* const texture);

		~Sprite();

		/// <summary>
		/// Gets the size of the Sprite.
		/// </summary>
		/// <returns>The width * height.</returns>
		constexpr int size() const { return width * height; }
		/// <summary>
		/// Gets the rect of the Sprite.
		/// </summary>
		/// <returns>A Rect that has the pivot offset as a position, and the Sprite's width and height.</returns>
		inline Rect rect() const { return Rect(math_floorToInt(m_offset.x), math_floorToInt(m_offset.y), width, height); }
		/// <summary>
		/// Sets the render pivot of this Sprite.
		/// </summary>
		/// <param name="pivot"></param>
		void setPivot(PointF const& pivot) { m_offset = PointF(-pivot.x * static_cast<float>(width), -pivot.y * static_cast<float>(height)); }
		/// <summary>
		/// Gets the pivot of this Sprite, as a pixel offset.
		/// </summary>
		/// <returns>The offset.</returns>
		inline PointF offset() const { return m_offset; }
		/// <summary>
		/// Gets the Surface of this Sprite.
		/// </summary>
		/// <returns>The Surface.</returns>
		inline SDL_Surface* surface() const { return mp_surface; }
		/// <summary>
		/// Gets the Texture of this Sprite.
		/// </summary>
		/// <returns>The Texture.</returns>
		inline SDL_Texture* texture() const { return mp_texture; }
		/// <summary>
		/// Gets the mask for this Sprite.
		/// </summary>
		/// <returns>The mask.</returns>
		inline Mask* mask() const { return mp_mask; }
		/// <summary>
		/// Creates the Mask for this Sprite, if needed.
		/// </summary>
		void createMask();

		/// <summary>
		/// Gets the color using the relative positions of the given X and Y positions.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		Color getColor(int const x, int const y) const;

		/// <summary>
		/// Gets the pixel at the given X and Y positions.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		Color at(int const x, int const y) const;

		/// <summary>
		/// Gets the array of pixels from the surface for this Sprite.
		/// </summary>
		/// <returns></returns>
		inline color_t* pixels() const;

		/// <summary>
		/// Creates a Sprite from a part of this Sprite.
		/// </summary>
		/// <param name="rect"></param>
		/// <param name="renderer"></param>
		/// <param name="pivot"></param>
		/// <returns></returns>
		Sprite* slice(Rect const& rect, SDL_Renderer* const renderer, PointF const& pivot = PointF()) const;

		/// <summary>
		/// Creates a new copy of this Sprite and returns it.
		/// </summary>
		/// <param name="renderer"></param>
		/// <returns></returns>
		Sprite* copy(SDL_Renderer* const renderer) const;
	};
}

