#pragma once

#include "M_PointF.h"
#include "M_Stopwatch.h"
#include "M_Font.h"
#include "M_Music.h"
#include "M_Sound.h"
#include <string>
#include <vector>
#include <SDL.h>

constexpr char const* const RESOURCES_DIRECTORY = "Resources";

namespace minty
{
	class Animation;
	class Sprite;
	class ProceduralSprite;

	MINTY_API std::string* resources_load_text(std::string const& path);

	MINTY_API std::vector<std::string>* resources_load_lines(std::string const& path);

	MINTY_API Font* resources_load_font(std::string const& path, int const size);

	MINTY_API Music* resources_load_music(std::string const& path);

	MINTY_API Sound* resources_load_sound(std::string const& path);

	MINTY_API SDL_Surface* resources_load_image(std::string const& path);

	MINTY_API Sprite* resources_load_sprite(std::string const& path, SDL_Renderer* const renderer, PointF const& pivot = PointF());

	MINTY_API ProceduralSprite* resources_load_proceduralSprite(std::string const& path, std::vector<std::string> const& artsPaths, SDL_Renderer* const renderer, PointF const& pivot = PointF());

	MINTY_API Animation* resources_load_animation_single(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, PointF const& pivot = PointF());

	MINTY_API std::vector<Animation*> resources_load_animation_multiple(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation, PointF const& pivot = PointF());

	MINTY_API SDL_Surface** resources_load_surfaces(std::string const& path, std::string const& extension, int const count);

	MINTY_API std::vector<SDL_Surface*>* resources_load_all_surfaces(std::string const& path, std::string const& extension);

	MINTY_API std::vector<Sprite*>* resources_load_all_sprites(std::string const& path, std::string const& extension, SDL_Renderer* const renderer, PointF const& pivot = PointF());
}