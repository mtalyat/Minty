#pragma once

#include "M_Object.h"
#include <SDL_ttf.h>
#include <unordered_map>

namespace minty
{
	class FontManager
		: public Object
	{
	private:
		std::unordered_map<std::string, TTF_Font*>* mp_fonts;

	public:
		FontManager();

		~FontManager();
	};
}