#pragma once

#include "M_Object.h"
#include "M_Sprite.h"
#include "M_Stopwatch.h"

namespace minty
{
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

		static Animation* fromSprite_single(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, elapsed_t const frameTime, bool const looping);

		static std::vector<Animation*> fromSprite_multiple(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, elapsed_t const frameTime, bool const looping, int const framesPerAnimation);
	};
}