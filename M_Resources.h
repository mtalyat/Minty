#pragma once

#include "M_Path.h"
#include "M_Sprite.h"
#include <string>
#include <vector>
#include <SDL.h>

constexpr char const* const RESOURCES_DIRECTORY = "Resources";

namespace minty
{
	MINTY_API inline std::string* resources_load_text(std::string const& path);

	MINTY_API inline std::vector<std::string>* resources_load_lines(std::string const& path);

	MINTY_API SDL_Surface* resources_load_image(std::string const& path);

	MINTY_API Sprite* resources_load_sprite(std::string const& path, SDL_Renderer* const renderer);

	MINTY_API SDL_Surface** resources_load_images(std::string const& path, std::string const& extension, int const count);

	MINTY_API std::vector<SDL_Surface*>* resources_load_all_images(std::string const& path, std::string const& extension);
}