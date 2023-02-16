#pragma once

#include "M_Object.h"
#include "M_Stopwatch.h"
#include <SDL.h>

namespace minty
{
	class Sprite;
	class ProceduralSprite;

	/// <summary>
	/// Holds data for one animation.
	/// </summary>
	class MINTY_API Animation
		: public Object
	{
	private:
		Sprite** mp_sprites;

	public:
		int const frameCount;
		elapsed_t const frameTime;
		bool const isLooping;

	public:
		Animation(Sprite** sprites, int const count, elapsed_t const time, bool const looping);

		~Animation();

		Sprite* operator[](int const index) const
		{
			return mp_sprites[index];
		}

		Sprite* at(int const index) const
		{
			return mp_sprites[index];
		}

		static Animation* fromSprite_single(Sprite* const sprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping);

		static std::vector<Animation*> fromSprite_multiple(Sprite* const sprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation);

		static Animation* fromSprite_single_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping);

		static std::vector<Animation*> fromSprite_multiple_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation);
	};
}