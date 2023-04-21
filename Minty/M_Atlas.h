#pragma once

#include "M_Object.h"
#include "M_Sprite.h"
#include <SDL.h>

namespace minty
{
	/// <summary>
	/// Holds a 2D array of Sprites, which all originate from a single Sprite.
	/// </summary>
	class MINTY_API Atlas
		: public Object
	{
	private:
		// width of the 2D array
		int m_widthInTiles;
		// height of the 2D array
		int m_heightInTiles;
		// 2D array
		Sprite** mp_tiles;

	public:
		/// <summary>
		/// Creates a new Atlas from the given Sprite. The Atlas will be generated using the given tile width and tile height.
		/// </summary>
		/// <param name="sprite">The Sprite to generate the Atlas from/</param>
		/// <param name="tileWidth">The width in pixels of each tile within the Atlas.</param>
		/// <param name="tileHeight">The height in pixels of each tile within the Atlas.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="pivot">The pivot to be applied to each tile of the Atlas.</param>
		Atlas(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());

		~Atlas();

		/// <summary>
		/// Gets the Sprite at the given X and Y position.
		/// </summary>
		/// <param name="x">The column of the Sprite.</param>
		/// <param name="y">The row of the Sprite.</param>
		/// <returns>The Sprite at the given position.</returns>
		inline Sprite* at(int const x, int const y) const { return mp_tiles[y * m_widthInTiles + x]; }

		/// <summary>
		/// Gets the Sprite at the given index.
		/// </summary>
		/// <param name="index">The flattened index of the Sprite.</param>
		/// <returns>The Sprite at the given index.</returns>
		inline Sprite* at(int const index) const { return mp_tiles[index]; }

		/// <summary>
		/// Gets the 2D array of tiles within this Atlas.
		/// </summary>
		/// <returns>The 2D array of tiles.</returns>
		inline Sprite** getTiles() const { return mp_tiles; }

		/// <summary>
		/// Gets the total number of tiles within this Atlas.
		/// </summary>
		/// <returns>The number of tiles.</returns>
		constexpr int getSize() const { return m_widthInTiles * m_heightInTiles; }

		/// <summary>
		/// Generates a 2D array of Sprite tiles from the given Sprite.
		/// </summary>
		/// <param name="sprite">The Sprite to generate the tiles from.</param>
		/// <param name="tileWidth">The width of each tile in pixels.</param>
		/// <param name="tileHeight">The height of each tile in pixels.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="pivot">The pivot to be applied to each Sprite.</param>
		/// <returns>A 2D array of Sprite tiles.</returns>
		static Sprite** generateTiles(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());

		/// <summary>
		/// Generates an Atlas from the Resources folder.
		/// </summary>
		/// <param name="path">The path to the texture in the Resources folder.</param>
		/// <param name="tileWidth">The width of each tile in pixels.</param>
		/// <param name="tileHeight">The height of each tile in pixels.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="pivot">The pivot to be applied to each Sprite.</param>
		/// <returns>An Atlas generated from the resource.</returns>
		static Atlas* fromResources(std::string const& path, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, PointF const& pivot = PointF());
	};
}