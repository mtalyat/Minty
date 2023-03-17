#include "pch.h"
#include "M_Sprite.h"
#include "M_Color.h"
#include "M_Debug.h"
#include "M_Mask.h"

namespace minty
{	
	Sprite::Sprite(SDL_Surface* const surface, SDL_Renderer* const renderer)
		: Sprite(surface, SDL_CreateTextureFromSurface(renderer, surface))
	{
		// allow for transparency
		SDL_SetTextureBlendMode(mp_texture, SDL_BLENDMODE_BLEND);
	}

	Sprite::Sprite(SDL_Texture* const texture, int const w, int const h)
		: width(w)
		, height(h)
		, m_offset()
		, mp_surface(nullptr)
		, mp_texture(texture)
		, mp_mask(nullptr)
	{}

	Sprite::Sprite(SDL_Surface* const surface, SDL_Texture* const texture)
		: width(surface->w)
		, height(surface->h)
		, m_offset()
		, mp_surface(surface)
		, mp_texture(texture)
		, mp_mask(nullptr)
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
		SDL_SetSurfaceBlendMode(mp_surface, SDL_BLENDMODE_NONE);
	}
	
	Sprite::~Sprite()
	{
		SDL_DestroyTexture(mp_texture);

		if (mp_mask)
		{
			delete mp_mask;
		}
	}

	void Sprite::generateMask()
	{
		if (mp_mask)
		{
			return;
		}

		// mask does not exist, generate it
		mp_mask = Mask::fromSprite(this);
	}

	Color Sprite::getColor(int const x, int const y) const
	{
		// get the pixel pos within this sprite
		int xFixed = math_mod_positive(x, width);
		int yFixed = math_mod_positive(y, height);

		// return pixel at position
		return at(xFixed, yFixed);
	}

	Color Sprite::at(int const x, int const y) const
	{
		// return pixel at position
		return Color(static_cast<Uint32*>(mp_surface->pixels)[y * width + x]);
	}

	color_t* Sprite::pixels() const
	{
		return static_cast<color_t*>(mp_surface->pixels);
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
