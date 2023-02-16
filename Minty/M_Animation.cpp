#include "pch.h"
#include "M_Animation.h"
#include "M_Atlas.h"
#include "M_Sprite.h"
#include "M_ProceduralSprite.h"

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

	Animation* Animation::fromSprite_single(Sprite* const sprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping)
	{
		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		return new Animation(Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer), widthInTiles * heightInTiles, frameTime, looping);
	}
	
	std::vector<Animation*> Animation::fromSprite_multiple(Sprite* const sprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation)
	{
		if (!framesPerAnimation.size())
		{
			// no animations for some reason
			return std::vector<Animation*>();
		}
		
		std::vector<Animation*> animations;

		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		// get sprites
		Sprite** tiles = Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer);

		// create an animation for every X frames
		for (size_t i = 0, j = 0; i < widthInTiles * heightInTiles && j + framesPerAnimation[j] < framesPerAnimation.size(); i += framesPerAnimation[j], j++)
		{
			animations.push_back(new Animation(&tiles[i], framesPerAnimation[j], frameTime, looping));
		}

		return animations;
	}
	
	Animation* Animation::fromSprite_single_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping)
	{
		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		// get raw tiles
		Sprite** raw = Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer);

		int const size = widthInTiles * heightInTiles;

		// create procedural sprites
		 Sprite** tiles = proceduralSprite->createMultiple(raw, size, renderer);

		// done with raw sprites
		delete[] raw;

		// animation complete
		return new Animation(tiles, widthInTiles * heightInTiles, frameTime, looping);
	}
	
	std::vector<Animation*> Animation::fromSprite_multiple_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation)
	{
		if (!framesPerAnimation.size())
		{
			// no animations for some reason
			return std::vector<Animation*>();
		}

		std::vector<Animation*> animations;

		// calculate number of sprites
		int widthInTiles = sprite->width / tileWidth;
		int heightInTiles = sprite->height / tileHeight;

		// get sprites
		Sprite** tiles = Atlas::generateTiles(sprite, tileWidth, tileHeight, renderer);

		// create an animation for every X frames
		for (size_t i = 0, j = 0; i < widthInTiles * heightInTiles && j + framesPerAnimation[j] < framesPerAnimation.size(); i += framesPerAnimation[j], j++)
		{
			animations.push_back(new Animation(proceduralSprite->createMultiple(&tiles[i], framesPerAnimation[j], renderer), framesPerAnimation[j], frameTime, looping));
		}

		return animations;
	}
}
