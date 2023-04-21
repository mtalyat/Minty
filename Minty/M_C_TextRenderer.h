#pragma once

#include "M_Main.h"
#include "M_Text.h"

namespace minty
{
	/// <summary>
	/// Renders Text to the Screen.
	/// </summary>
	struct MINTY_API TextRenderer
	{
		/// <summary>
		/// The Text to render.
		/// </summary>
		Text* text;
	};
}