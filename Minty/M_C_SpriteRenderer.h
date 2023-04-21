#pragma once

#include "M_Main.h"
#include "M_Sprite.h"

namespace minty
{
	/// <summary>
	/// Renders a Sprite to the Screen.
	/// </summary>
	struct MINTY_API SpriteRenderer
	{
		/// <summary>
		/// The Sprite to be rendered.
		/// </summary>
		Sprite* sprite;
	};
}