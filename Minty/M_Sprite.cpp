#include "pch.h"
#include "M_Sprite.h"
#include "M_Color.h"
#include "M_Debug.h"

namespace minty
{	
	Sprite::Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer)
		: Sprite(surface, SDL_CreateTextureFromSurface(renderer, surface))
	{}

	Sprite::Sprite(SDL_Texture* const texture, int const w, int const h)
		: width(w)
		, height(h)
		, m_offset()
		, mp_surface(nullptr)
		, mp_texture(texture)
	{}

	Sprite::Sprite(SDL_Surface* const surface, SDL_Texture* const texture)
		: width(surface->w)
		, height(surface->h)
		, m_offset()
		, mp_surface(surface)
		, mp_texture(texture)
	{
		if (!mp_surface)
		{
			Debug::logWarning("Created a Sprite with a null surface!");
		}

		if (!mp_texture)
		{
			Debug::logWarning("Created a Sprite with a null texture!");
		}

		// for slicing, make sure the blend mode is set to none
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	}
	
	Sprite::~Sprite()
	{
		SDL_DestroyTexture(mp_texture);
	}

	Color Sprite::getColor(int const x, int const y)
	{
		// get the pixel pos within this sprite
		int xFixed = math_mod_positive(x, width);
		int yFixed = math_mod_positive(y, height);

		// return pixel at position
		return at(xFixed, yFixed);
	}

	Color Sprite::at(int const x, int const y)
	{
		// return pixel at position
		return static_cast<Color*>(mp_surface->pixels)[y * width + x];
	}

	Sprite* Sprite::slice(Rect const& rect, SDL_Renderer* const renderer) const
	{
		// create new surface of area we want
		SDL_Surface* newSurface = SDL_CreateRGBSurface(0, rect.width, rect.height, mp_surface->format->BitsPerPixel, mp_surface->format->Rmask, mp_surface->format->Gmask, mp_surface->format->Bmask, mp_surface->format->Amask);

		SDL_Rect sdlRect = rect.toSDL();

		// copy area to that new surface
		if (SDL_BlitSurface(mp_surface, &sdlRect, newSurface, nullptr))
		{
			Debug::logErrorSDL(25, "Could not blit surface when slicing.");

			return nullptr;
		}

		// return new sprite
		return new Sprite(newSurface, renderer);
	}
}
