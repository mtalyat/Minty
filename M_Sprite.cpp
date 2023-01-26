#include "pch.h"
#include "M_Sprite.h"

namespace minty
{
	inline Sprite::Sprite(SDL_Texture* const texture, int const width, int const height)
		: m_width(width)
		, m_height(height)
		, mp_surface(nullptr)
		, mp_texture(texture)
	{}
	
	inline Sprite::Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer)
		: m_width(surface->w)
		, m_height(surface->h)
		, mp_surface(surface)
		, mp_texture(SDL_CreateTextureFromSurface(renderer, surface))
	{}
	
	inline Sprite::~Sprite()
	{
		SDL_DestroyTexture(mp_texture);
	}
	
	inline void Sprite::setTexture(SDL_Texture* const texture, int const width, int const height)
	{
		mp_texture = texture;
		m_width = width;
		m_height = height;
	}

	inline void Sprite::replaceTexture(SDL_Texture* const newTexture, int const width, int const height)
	{
		// destroy old, set new
		SDL_DestroyTexture(mp_texture);
		setTexture(newTexture, width, height);
	}

	void Sprite::replaceSurface(SDL_Surface* const newSurface, SDL_Renderer* const renderer)
	{
		SDL_FreeSurface(mp_surface);
		mp_surface = newSurface;
		replaceTexture(SDL_CreateTextureFromSurface(renderer, newSurface), newSurface->w, newSurface->h);
	}
}
