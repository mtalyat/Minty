#include "pch.h"
#include "M_Animation.h"
#include "M_Atlas.h"

namespace minty
{
	Animation::Animation(Sprite** sprites, int const count, elapsed_t const time, bool const looping)
		: mp_sprites(sprites)
		, frameCount(count)
		, frameTime(time)
		, isLooping(looping)
	{}

	Animation::~Animation()
	{
		// delete all sprites?
		for (size_t i = 0; i < frameCount; i++)
		{
			delete mp_sprites[i];
		}

		//delete[] mp_sprites;
	}

	Animation* Animation::fromSprite_single(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, elapsed_t const frameTime, bool const looping)
	{
		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		return new Animation(Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer), widthInTiles * heightInTiles, frameTime, looping);
	}

	std::vector<Animation*> Animation::fromSprite_multiple(Sprite* const sprite, int const tileWidth, int const tileHeight, SDL_Renderer* const renderer, elapsed_t const frameTime, bool const looping, int const framesPerAnimation)
	{
		std::vector<Animation*> animations;

		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		// get sprites
		Sprite** tiles = Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer);

		// create an animation for every X frames

		for (int i = 0; i < widthInTiles * heightInTiles; i += framesPerAnimation)
		{
			animations.push_back(new Animation(&tiles[i], framesPerAnimation, frameTime, looping));
		}

		return animations;
	}
}
