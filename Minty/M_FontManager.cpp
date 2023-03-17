#include "pch.h"
#include "M_FontManager.h"

minty::FontManager::FontManager()
	: mp_fonts(new std::unordered_map<std::string, TTF_Font*>())
{
}

minty::FontManager::~FontManager()
{
	// free each font stored in manager
	for (auto const& pair : *mp_fonts)
	{
		delete pair.second;
	}

	delete mp_fonts;
}
