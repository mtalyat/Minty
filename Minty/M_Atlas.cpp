#include "pch.h"
#include "M_Atlas.h"

#include "M_Resources.h"

namespace minty
{
	Atlas::Atlas(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer)
		: m_widthInTiles(sprite->width / tileWidth)
		, m_heightInTiles(sprite->width / tileHeight)
		, mp_tiles(generateTiles(sprite, tileWidth, tileHeight, renderer))
	{}

	Atlas::~Atlas()
	{
		// delete each sprite
		for (size_t i = 0; i < size(); i++)
		{
			delete mp_tiles[i];
		}

		// delete array
		delete[] mp_tiles;
	}

	Sprite** Atlas::generateTiles(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer)
	{
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		Sprite** tiles = new Sprite * [widthInTiles * heightInTiles];

		for (int row = 0; row < heightInTiles; row++)
		{
			for (int col = 0; col < widthInTiles; col++)
			{
				tiles[row * widthInTiles + col] = sprite->slice(Rect(col * tileWidth, row * tileHeight, tileWidth, tileHeight), renderer);
			}
		}

		return tiles;
	}
	
	Atlas* Atlas::fromResources(std::string const& path, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer)
	{
		// get sprite
		Sprite* sprite = resources_load_sprite(path, renderer);

		// use sprite
		Atlas* atlas = new Atlas(sprite, tileWidth, tileHeight, renderer);

		// delete sprite
		delete sprite;

		return atlas;
	}
}
