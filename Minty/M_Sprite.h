#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include <SDL.h>

namespace minty
{
	class MINTY_API Sprite :
		public Object
	{
	public:
		int const width;
		int const height;
	private:
		SDL_Surface* mp_surface;
		SDL_Texture* mp_texture;

	public:
		Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer);

		~Sprite();

		constexpr int size() const { return width * height; }
		inline Rect rect() const { return Rect(0, 0, width, height); }
		inline SDL_Surface* surface() const { return mp_surface; }
		inline SDL_Texture* texture() const { return mp_texture; }

		Sprite* slice(Rect const& rect, SDL_Renderer* const renderer) const;
	};
}

