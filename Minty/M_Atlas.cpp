#include "pch.h"
#include "M_Atlas.h"

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
}