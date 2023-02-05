#include "pch.h"
#include "M_Resources.h"
#include "M_File.h"
#include "M_Debug.h"
#include <SDL_image.h>

namespace minty
{
	std::string* resources_load_text(std::string const& path)
	{
		return file_readAllText(path_combine(RESOURCES_DIRECTORY, path));
	}

	std::vector<std::string>* resources_load_lines(std::string const& path)
	{
		return file_readAllLines(path_combine(RESOURCES_DIRECTORY, path));
	}

	SDL_Surface* resources_load_image(std::string const& path)
	{
		SDL_Surface* surface = IMG_Load(path_combine(RESOURCES_DIRECTORY, path).c_str());

		if (!surface)
		{
			Debug::logErrorSDL(7, std::format("Could not load image at path \"{0}\".", path));
		}

		return surface;
	}

	Sprite* resources_load_sprite(std::string const& path, SDL_Renderer* const renderer)
	{
		// get the surface, use it to create a texture for the sprite, free the surface, return the sprite

		SDL_Surface* surface = resources_load_image(path);
		Sprite* sprite = new Sprite(surface, renderer);
		return sprite;
	}

	SDL_Surface** resources_load_surfaces(std::string const& path, std::string const& extension, int const count)
	{
		SDL_Surface** surfaces = new SDL_Surface * [count];

		std::string basePath = path_combine(RESOURCES_DIRECTORY, path);

		std::string finalPath;

		for (int i = 0; i < count; i++)
		{
			finalPath = basePath + std::to_string(i) + extension;

			if (!(surfaces[i] = IMG_Load(finalPath.c_str())))
			{
				Debug::logErrorSDL(8, std::format("Failed to create image from resources at path: \"{0}\"", finalPath));
			}
		}

		return surfaces;
	}

	std::vector<SDL_Surface*>* resources_load_all_surfaces(std::string const& path, std::string const& extension)
	{
		std::vector<SDL_Surface*>* surfaces = new std::vector<SDL_Surface*>();

		std::string basePath = path_combine(RESOURCES_DIRECTORY, path);

		std::string finalPath = basePath + "0" + extension;

		size_t i = 0;
		SDL_Surface* surface;
		// while file exists, add to vector
		while (file_exists(finalPath))
		{
			// add to vector
			surface = IMG_Load(finalPath.c_str());

			if (!surface)
			{
				Debug::logErrorSDL(9, std::format("Failed to create image from resources at path: \"{0}\"", finalPath));
				break;
			}

			surfaces->push_back(surface);

			i++;

			// get next path
			finalPath = basePath + std::to_string(i) + extension;
		}

		return surfaces;
	}
	
	MINTY_API std::vector<Sprite*>* resources_load_all_sprites(std::string const& path, std::string const& extension, SDL_Renderer* const renderer)
	{
		std::vector<Sprite*>* sprites = new std::vector<Sprite*>();

		std::string basePath = path_combine(RESOURCES_DIRECTORY, path);

		std::string finalPath = basePath + "0" + extension;

		size_t i = 0;
		SDL_Surface* surface;
		// while file exists, add to vector
		while (file_exists(finalPath))
		{
			// add to vector
			sprites->push_back(resources_load_sprite(finalPath, renderer));

			i++;

			// get next path
			finalPath = basePath + std::to_string(i) + extension;
		}

		return sprites;
	}
}
