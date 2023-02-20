#pragma once

#include "M_Object.h"
#include "M_Color.h"
#include <map>
#include <SDL.h>

namespace minty
{
	class Sprite;

	/// <summary>
	/// Holds data for a procedural sprite. A procedural sprite is used as a lookup table to generate sprites, using a procedural sprite and a sprite that contains the art (aka a "skin").
	/// </summary>
	class MINTY_API ProceduralSprite
		: public Object
	{
	private:
		std::map<color_t, int>* mp_indices;
		Sprite* const* mp_textures;
		size_t m_texturesCount;

	public:
		int const width, height;

	public:
		ProceduralSprite(Sprite const* const sprite, Sprite* const* const textures, size_t const texturesCount);

		/// <summary>
		/// Sets the pieces of art (aka 'skins') for this procedural sprite.
		/// </summary>
		/// <param name="textures"></param>
		/// <param name="texturesCount"></param>
		void setArts(Sprite* const* textures, size_t const texturesCount);

		/// <summary>
		/// Creates a Sprite and generates all pieces of art (in order) to the new Sprite, then returns it.
		/// </summary>
		/// <param name="design"></param>
		/// <param name="arts"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		Sprite* create(Sprite const* const design, SDL_Renderer* const renderer);

		/// <summary>
		/// Creates a Sprite from multiple layers of designs, and generates all pieces of art (in order) to the new Sprite, then returns it.
		/// </summary>
		/// <param name="designs"></param>
		/// <param name="count"></param>
		/// <param name="renderer"></param>
		/// <returns></returns>
		Sprite* create(Sprite* const* const designs, int const count, SDL_Renderer* const renderer);

		/// <summary>
		/// Creates multiple Sprites and generates all pieces of art (in order) to the new Sprites, then returns them.
		/// </summary>
		/// <param name="designs"></param>
		/// <param name="count"></param>
		/// <param name="renderer"></param>
		/// <returns></returns>
		Sprite** createMultiple(Sprite* const* const designs, int const count, SDL_Renderer* const renderer);

		/// <summary>
		/// Creates multiple Sprites from multiple layers of designs, and generates all pieces of art (in order) to the new Sprites, then returns them.
		/// </summary>
		/// <param name="designs"></param>
		/// <param name="count"></param>
		/// <param name="layerCount"></param>
		/// <param name="renderer"></param>
		/// <returns></returns>
		Sprite** createMultiple(Sprite* const* const designs, int const frameCount, int const layerCount, SDL_Renderer* const renderer);

	private:
		/// <summary>
		/// Finds the index of the ID at the given X and Y coordinates.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		int at(int const x, int const y);

		/// <summary>
		/// Gets the index of the given ID.
		/// </summary>
		/// <param name="id"></param>
		/// <returns></returns>
		int at(color_t const id);

		/// <summary>
		/// Generates pixels based on the design sprite, using the art sprite. The design sprite is used with this ProceduralSprite to cross reference the IDs with the indices.
		/// If the ID from the design does not exist within this ProceduralSprite, then the corresponding pixel in pixels is left unchanged.
		/// </summary>
		/// <param name="sprites"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		void generate(color_t* const pixels, Sprite const* const design, Sprite const* const art);
	};
}