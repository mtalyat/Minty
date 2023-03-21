#pragma once

#include "M_Object.h"
#include "M_Sprite.h"
#include <SDL.h>

namespace minty
{
	/// <summary>
	/// Holds an atlas of sprites, which all originate from a single sprite.
	/// </summary>
	class MINTY_API Atlas
		: public Object
	{
	private:
		int m_widthInTiles;
		int m_heightInTiles;
		Sprite** mp_tiles;

	public:
		Atlas(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());

		~Atlas();

		inline Sprite* at(int const x, int const y) const { return mp_tiles[y * m_widthInTiles + x]; }

		inline Sprite* at(int const index) const { return mp_tiles[index]; }

		inline Sprite** tiles() const { return mp_tiles; }

		constexpr int size() const { return m_widthInTiles * m_heightInTiles; }

		static Sprite** generateTiles(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());

		static Atlas* fromResources(std::string const& path, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());
	};
}