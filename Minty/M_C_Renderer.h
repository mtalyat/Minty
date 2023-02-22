#pragma once

#include "M_Main.h"
#include "M_Sprite.h"

namespace minty
{
	/// <summary>
	/// A component that renders a Sprite to the screen.
	/// </summary>
	struct MINTY_API Renderer
	{
		/// <summary>
		/// The Sprite to be rendered.
		/// </summary>
		Sprite* sprite;

		/// <summary>
		/// The rendering index of this Renderer.
		/// </summary>
		int index;

		/// <summary>
		/// Is this Sprite invisible?
		/// </summary>
		bool invisible;

		/// <summary>
		/// Is the Renderer flipped?
		/// </summary>
		int flip;

		inline SDL_RendererFlip getFlip() const { return static_cast<SDL_RendererFlip>(flip); }

		/// <summary>
		/// Checks if this SpriteRenderer is visible.
		/// </summary>
		/// <returns></returns>
		constexpr bool isVisible() const { return !invisible && sprite; }
	};
}