#pragma once

#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_Color.h"
#include <SDL.h>

namespace minty
{
	class MINTY_API Screen :
		public Object
	{
	private:
		SDL_Window* mp_window;
		SDL_Renderer* mp_renderer;
		SDL_Texture* mp_background_texture;
		Color m_background_color;

	public:
		/// <summary>
		/// The width of this Screen in pixels.
		/// </summary>
		int const width;

		/// <summary>
		/// The height of this Screen in pixels.
		/// </summary>
		int const height;

		/// <summary>
		/// Creates a new Screem (Window) with the given title, width and height.
		/// </summary>
		/// <param name="title"></param>
		/// <param name="w"></param>
		/// <param name="h"></param>
		Screen(std::string const& title, int const w, int const h);

		~Screen();

		/// <summary>
		/// Gets the Rect of this Screen.
		/// </summary>
		/// <returns></returns>
		inline Rect rect() const;

		/// <summary>
		/// Gets the size of this Screen.
		/// </summary>
		/// <returns></returns>
		inline Point size() const;

		/// <summary>
		/// Gets the Window of this Screen.
		/// </summary>
		/// <returns></returns>
		inline SDL_Window* const window() const { return mp_window; }

		/// <summary>
		/// Gets the Renderer of this Screen.
		/// </summary>
		/// <returns></returns>
		inline SDL_Renderer* const renderer() const { return mp_renderer; }

		/// <summary>
		/// Sets the background Texture for the Screen.
		/// </summary>
		/// <param name="tex"></param>
		inline void setBackgroundTexture(SDL_Texture* const tex) { mp_background_texture = tex; }

		/// <summary>
		/// Gets the background Texture for the Screen.
		/// </summary>
		/// <returns></returns>
		inline SDL_Texture* const backgroundTexture() const { return mp_background_texture; }

		/// <summary>
		/// Sets the background Color for the Screen.
		/// </summary>
		/// <param name="color"></param>
		inline void setBackgroundColor(Color const color) { m_background_color = color; }

		/// <summary>
		/// Gets the background Color for the Screen.
		/// </summary>
		/// <returns></returns>
		inline Color const backgroundColor() const { return m_background_color; }

		std::string const toString() const override;
	};
}