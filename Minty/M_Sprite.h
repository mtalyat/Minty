#pragma once

#include "M_Object.h"
#include <SDL.h>

namespace minty
{
	class MINTY_API Sprite :
		public Object
	{
	private:
		int m_width;
		int m_height;
		SDL_Surface* mp_surface;
		SDL_Texture* mp_texture;

	public:
		Sprite(SDL_Texture* const texture, int const width, int const height);

		Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer);

		~Sprite();

		constexpr int width() const { return m_width; }
		constexpr int height() const { return m_height; }
		constexpr int size() const { return m_width * m_height; }
		inline SDL_Surface* surface() const { return mp_surface; }
		inline SDL_Texture* texture() const { return mp_texture; }

		void setTexture(SDL_Texture* const texture, int const width, int const height);
		void replaceTexture(SDL_Texture* const newTexture, int const width, int const height);
		void replaceSurface(SDL_Surface* const newSurface, SDL_Renderer* const renderer);
	};
}

