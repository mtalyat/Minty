#include "pch.h"
#include "M_Sprite.h"
#include "M_Color.h"
#include "M_Debug.h"

namespace minty
{	
	Sprite::Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer)
		: width(surface->w)
		, height(surface->h)
		, mp_surface(surface)
		, mp_texture(SDL_CreateTextureFromSurface(renderer, surface))
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
