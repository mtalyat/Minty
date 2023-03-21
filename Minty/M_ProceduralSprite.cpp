#include "pch.h"
#include "M_ProceduralSprite.h"

#include "M_Sprite.h"
#include "M_Debug.h"

namespace minty
{
	ProceduralSprite::ProceduralSprite(Sprite const* const sprite, Sprite* const* const textures, size_t const texturesCount)
		: mp_indices(new std::map<color_t, int>())
		, mp_textures(textures)
		, m_texturesCount(texturesCount)
		, width(sprite->width)
		, height(sprite->height)
	{
		// for each pixel within the sprite, create a unique ID, then emplace that within the map
		// the value for each ID will be an index to the location of that pixel in the sprite

		color_t color;
		auto pixels = sprite->pixels();

		for (int i = 0; i < sprite->size(); i++)
		{
			color = pixels[i];

			// only use if color has an alpha
			if (Color::getA(color) > CHANNEL_MIN)
			{
				// if there is an alpha, then we will use the color
				if (!mp_indices->try_emplace(color, i).second)
				{
					// could not emplace: key exists
					Debug::logError(28, std::format("Duplicate color in ProceduralSprite ({}).", Color(color).toString()));
				}
			}
		}
	}

	void ProceduralSprite::setArts(Sprite* const* textures, size_t const texturesCount)
	{
		mp_textures = textures;
		m_texturesCount = texturesCount;
	}

	Sprite* ProceduralSprite::create(Sprite const* const design, SDL_Renderer* const renderer, PointF const& pivot)
	{
		// create a surface to modify
		SDL_Surface* const designSurface = design->surface();
		SDL_Surface* surface = SDL_CreateRGBSurface(0, designSurface->w, designSurface->h, designSurface->format->BitsPerPixel, designSurface->format->Rmask, designSurface->format->Gmask, designSurface->format->Bmask, designSurface->format->Amask);

		// lock so the pixels can be edited
		if (SDL_LockSurface(designSurface))
		{
			Debug::logErrorSDL(27, "Could not lock surface.");
			return nullptr;
		}

		// edit surface
		color_t* pixels = static_cast<color_t*>(surface->pixels);

		// apply each layer
		for (int i = 0; i < m_texturesCount; i++)
		{
			generate(pixels, design, mp_textures[i]);
		}

		// done editing
		SDL_UnlockSurface(surface);

		Sprite* sprite = new Sprite(surface, renderer);
		sprite->setPivot(pivot);

		return sprite;
	}

	Sprite* ProceduralSprite::create(Sprite* const* const designs, int const count, SDL_Renderer* const renderer, PointF const& pivot)
	{
		if (count <= 0)
		{
			return nullptr;
		}

		// create a surface to modify
		SDL_Surface* const designSurface = designs[0]->surface();
		SDL_Surface* surface = SDL_CreateRGBSurface(0, designSurface->w, designSurface->h, designSurface->format->BitsPerPixel, designSurface->format->Rmask, designSurface->format->Gmask, designSurface->format->Bmask, designSurface->format->Amask);

		// lock so the pixels can be edited
		if (SDL_LockSurface(surface))
		{
			Debug::logErrorSDL(27, "Could not lock surface.");
			return nullptr;
		}

		// edit surface
		color_t* pixels = static_cast<color_t*>(surface->pixels);

		// apply each layer
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < m_texturesCount; j++)
			{
				generate(pixels, designs[i], mp_textures[j]);
			}
		}

		// done editing
		SDL_UnlockSurface(surface);

		Sprite* sprite = new Sprite(surface, renderer);
		sprite->setPivot(pivot);

		return sprite;
	}

	Sprite** ProceduralSprite::createMultiple(Sprite* const* const designs, int const count, SDL_Renderer* const renderer, PointF const& pivot)
	{
		Sprite** sprites = new Sprite * [count];

		for (int i = 0; i < count; i++)
		{
			sprites[i] = create(designs[i], renderer, pivot);
		}

		return sprites;
	}

	Sprite** ProceduralSprite::createMultiple(Sprite* const* const designs, int const frameCount, int const layerCount, SDL_Renderer* const renderer, PointF const& pivot)
	{
		Sprite** sprites = new Sprite * [frameCount];

		for (int i = 0; i < frameCount; i++)
		{
			sprites[i] = create(&designs[i * layerCount], layerCount, renderer, pivot);
		}

		return sprites;
	}

	int ProceduralSprite::at(int const x, int const y)
	{
		return at(y * width + x);
	}

	int ProceduralSprite::at(color_t const id)
	{
		auto found = mp_indices->find(id);

		if (found != mp_indices->end())
		{
			return found->second;
		}

		// index not found, must be an empty pixel
		return -1;
	}
	
	void ProceduralSprite::generate(color_t* const pixels, Sprite const* const design, Sprite const* const art)
	{
		// assume all same size
		// TODO: check ^

		color_t color;
		color_t id;
		int index;
		channel_t a;

		int const size = design->width * design->height;

		// designPixels and pixels will be same length
		color_t* const designPixels = design->pixels();

		// art pixels should be ok for bound checking, as any index should stay within the art bounds
		color_t* const artPixels = art->pixels();

		for (int i = 0; i < size; i++)
		{
			id = designPixels[i];

			// check design, if empty, ignore
			if (Color::getA(id) == CHANNEL_MIN)
			{
				//ignore, empty
				continue;
			}

			// has some alpha, check ID
			index = at(id);

			if (index == -1)
			{
				// no index for this given ID, ignore
				Debug::logError(29, std::format("No index found for given ID ({0})/({1})", id, Color(id).toString()));

				continue;
			}

			// valid index for this ID, get the color at that index
			color = artPixels[index];

			// if visible, write to pixels
			a = Color::getA(color);

			if (a == CHANNEL_MAX)
			{
				// full alpha, do not lerp
				pixels[i] = color;

				//Debug::log(std::format("[{0}] Set {1} to {2}.", i, Color(id).toString(), Color(color).toString()));
			}
			else if (a)
			{
				// partial alpha, but not zero, so lerp
				pixels[i] = Color::lerp_rgba(pixels[i], color, a / 255.0f);

				//Debug::log(std::format("[{0}] Set {1} to lerp {2}.", i, Color(id).toString(), Color(color).toString()));
			}
		}
	}
}
