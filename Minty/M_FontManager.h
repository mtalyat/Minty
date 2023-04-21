#pragma once

#include "M_Object.h"
#include <SDL_ttf.h>
#include <unordered_map>

namespace minty
{
	/// <summary>
	/// Manages fonts that are used within a game.
	/// </summary>
	class FontManager
		: public Object
	{
	private:
		// the fonts
		std::unordered_map<std::string, TTF_Font*>* mp_fonts;

	public:
		/// <summary>
		/// Creates a new FontManager.
		/// </summary>
		FontManager();

		~FontManager();
	};
}