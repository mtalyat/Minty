#pragma once

#include "M_Main.h"
#include "M_Sprite.h"

namespace minty
{
	/// <summary>
	/// A component that renders a Sprite to the screen.
	/// </summary>
	struct MINTY_API SpriteRenderer
	{
		/// <summary>
		/// The Sprite to be rendered.
		/// </summary>
		Sprite* sprite;

		/// <summary>
		/// Is this sprite invisible?
		/// </summary>
		bool invisible;
	};
}