#pragma once

#include "M_PointF.h"
#include "M_Stopwatch.h"
#include "M_Font.h"
#include "M_Audio_Music.h"
#include "M_Audio_Sound.h"
#include <string>
#include <vector>
#include <SDL.h>

constexpr char const* const RESOURCES_DIRECTORY = "Resources";

namespace minty
{
	class Animation;
	class Sprite;
	class ProceduralSprite;

	/// <summary>
	/// Loads the text from a resource file, as a string.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <returns>The string from the desired file.</returns>
	MINTY_API std::string* resources_load_text(std::string const& path);

	/// <summary>
	/// Loads the text lines from a resource file, as a vector of strings.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <returns>The lines from the desired file.</returns>
	MINTY_API std::vector<std::string>* resources_load_lines(std::string const& path);

	/// <summary>
	/// Loads a Font from a resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <param name="size">The point size of the Font.</param>
	/// <returns>The Font from the desired file.</returns>
	MINTY_API Font* resources_load_font(std::string const& path, int const size);

	/// <summary>
	/// Loads the .mp3 Music file from a resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <returns>The Music Audio from the desired file.</returns>
	MINTY_API Music* resources_load_music(std::string const& path);

	/// <summary>
	/// Loads the .wav Sound file from a resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <returns>The Sound Audio from the desired file.</returns>
	MINTY_API Sound* resources_load_sound(std::string const& path);

	/// <summary>
	/// Loads the .png Surface from a resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <returns>The Surface from the desired file.</returns>
	MINTY_API SDL_Surface* resources_load_image(std::string const& path);

	/// <summary>
	/// Loads the .png Sprite from a resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <param name="renderer">The Engine Renderer.</param>
	/// <param name="pivot">The pivot to apply to the Sprite.</param>
	/// <returns>The Sprite from the desired file.</returns>
	MINTY_API Sprite* resources_load_sprite(std::string const& path, SDL_Renderer* const renderer, PointF const& pivot = PointF());

	/// <summary>
	/// Loads the .png(s) and creates a ProceduralSprite from them, from the resource file(s).
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <param name="artsPaths">The paths to the art design files, relative to the resources folder.</param>
	/// <param name="renderer">The Engine Renderer.</param>
	/// <param name="pivot">The pivot to apply to the Sprite.</param>
	/// <returns>The created ProceduralSprite.</returns>
	MINTY_API ProceduralSprite* resources_load_proceduralSprite(std::string const& path, std::vector<std::string> const& artsPaths, SDL_Renderer* const renderer, PointF const& pivot = PointF());

	/// <summary>
	/// Loads the .png and creates an Animation from it, from the resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <param name="renderer">The Engine Renderer.</param>
	/// <param name="tileWidth">The width of each animation frame, in pixels.</param>
	/// <param name="tileHeight">The height of each animation frame, in pixels.</param>
	/// <param name="frameTime">The time for each frame.</param>
	/// <param name="looping">Does the Animation repeat?</param>
	/// <param name="pivot">The pivot to apply to each Sprite within the Animation.</param>
	/// <returns>The created Animation.</returns>
	MINTY_API Animation* resources_load_animation_single(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, PointF const& pivot = PointF());
	
	/// <summary>
	/// Loads the .png and creates multiple Animations from it, from the resource file.
	/// </summary>
	/// <param name="path">The path to the file, relative to the resources folder.</param>
	/// <param name="renderer">The Engine Renderer.</param>
	/// <param name="tileWidth">The width of each animation frame, in pixels.</param>
	/// <param name="tileHeight">The height of each animation frame, in pixels.</param>
	/// <param name="frameTime">The time for each frame.</param>
	/// <param name="looping">Does the Animation repeat?</param>
	/// <param name="framesPerAnimation">The number of frames per Animation.</param>
	/// <param name="pivot">The pivot to apply to each Sprite within the Animation.</param>
	/// <returns>The created Animations.</returns>
	MINTY_API std::vector<Animation*> resources_load_animation_multiple(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation, PointF const& pivot = PointF());

	/// <summary>
	/// Loads the number of surfaces that follow the same name as the given path, with "_X" postfixed to each file, where X is an integer, starting at 0.
	/// </summary>
	/// <param name="path">The path to the files, relative to the resources folder, with no extension.</param>
	/// <param name="extension">The extension of the file type.</param>
	/// <param name="count">The number of surfaces to load.</param>
	/// <returns>An array of Surface pointers.</returns>
	MINTY_API SDL_Surface** resources_load_surfaces(std::string const& path, std::string const& extension, int const count);

	/// <summary>
	/// Loads all of the surfaces that follow the same name as the given path, with "_X" postfixed to each file, where X is an integer, starting at 0.
	/// </summary>
	/// <param name="path">The path to the files, relative to the resource folder, with no extension.</param>
	/// <param name="extension">The extension of the file type.</param>
	/// <returns>A vector of Surface pointers.</returns>
	MINTY_API std::vector<SDL_Surface*>* resources_load_all_surfaces(std::string const& path, std::string const& extension);

	/// <summary>
	/// Loads all of the surfaces that follow the same name as the given path, with "_X" postfixed to each file, where X is an integer, starting at 0.
	/// </summary>
	/// <param name="path">The path to the files, relative to the resource folder, with no extension.</param>
	/// <param name="extension">The extension of the file type.</param>
	/// <param name="renderer">The Engine Renderer.</param>
	/// <param name="pivot">The pivot to apply to each Sprite.</param>
	/// <returns>A vector of Sprite pointers.</returns>
	MINTY_API std::vector<Sprite*>* resources_load_all_sprites(std::string const& path, std::string const& extension, SDL_Renderer* const renderer, PointF const& pivot = PointF());
}