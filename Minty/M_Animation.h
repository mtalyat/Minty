#pragma once

#include "M_Object.h"
#include "M_Stopwatch.h"
#include "M_Renderer.h"
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
		/// <summary>
		/// Creates a new Animation using the given Sprites and animation data.
		/// </summary>
		/// <param name="sprites">A pointer to an array of Sprite pointers.</param>
		/// <param name="count">The number of elements in the array of Sprite pointers.</param>
		/// <param name="time">The time for each frame.</param>
		/// <param name="looping">Does this animation loop?</param>
		Animation(Sprite** sprites, int const count, elapsed_t const time, bool const looping);

		~Animation();

		/// <summary>
		/// Indexes the Sprites in this Animation.
		/// </summary>
		/// <param name="index">The index of the Sprite.</param>
		/// <returns>The Sprite.</returns>
		Sprite* operator[](int const index) const
		{
			return mp_sprites[index];
		}

		/// <summary>
		/// Gets the Sprite at the given index.
		/// </summary>
		/// <param name="index">The index of the Sprite.</param>
		/// <returns>The Sprite.</returns>
		Sprite* at(int const index) const
		{
			return mp_sprites[index];
		}

		/// <summary>
		/// Splits up the given Sprite, and turns it into one Animation.
		/// </summary>
		/// <param name="sprite">The Sprite to extract the Animation from.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="tileWidth">The width of a frame.</param>
		/// <param name="tileHeight">The height of a frame.</param>
		/// <param name="frameTime">The time of each frame.</param>
		/// <param name="looping">Does the Animation loop?</param>
		/// <returns>An Animation.</returns>
		static Animation* fromSprite_single(Sprite* const sprite, Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping);

		/// <summary>
		/// Splits up the given Sprite, and turns it into multiple Animations.
		/// </summary>
		/// <param name="sprite">The Sprite to extract the Animations from.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="tileWidth">The width of a frame.</param>
		/// <param name="tileHeight">The height of a frame.</param>
		/// <param name="frameTime">The time of each frame.</param>
		/// <param name="looping">Does the Animation loop?</param>
		/// <param name="framesPerAnimation">The number of frames for each Animation.</param>
		/// <returns>A list of Animations.</returns>
		static std::vector<Animation*> fromSprite_multiple(Sprite* const sprite, Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation);

		/// <summary>
		/// Splits up the given Sprite, and turns it into one Animation, using the given ProceduralSprite.
		/// </summary>
		/// <param name="sprite">The Sprite to extract the Animation from.</param>
		/// <param name="proceduralSprite">The ProceduralSprite to generate each frame of the Animation with.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="tileWidth">The width of a frame.</param>
		/// <param name="tileHeight">The height of a frame.</param>
		/// <param name="frameTime">The time of each frame.</param>
		/// <param name="looping">Does the Animation loop?</param>
		/// <returns>An Animation.</returns>
		static Animation* fromSprite_single_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping);

		/// <summary>
		/// Splits up the given Sprite, and turns it into multiple Animations, using the given ProceduralSprite.
		/// </summary>
		/// <param name="sprite">The Sprite to extract the Animations from.</param>
		/// <param name="proceduralSprite">The ProceduralSprite to generate each frame of each Animation with.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="tileWidth">The width of a frame.</param>
		/// <param name="tileHeight">The height of a frame.</param>
		/// <param name="frameTime">The time of each frame.</param>
		/// <param name="looping">Does the Animation loop?</param>
		/// <param name="framesPerAnimation">The number of frames for each Animation.</param>
		/// <returns>A list of Animations.</returns>
		static std::vector<Animation*> fromSprite_multiple_p(Sprite* const sprite, ProceduralSprite* const proceduralSprite, Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation);
	};
}