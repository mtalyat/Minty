#include "pch.h"
#include "M_Resources.h"
#include "M_File.h"
#include "M_Debug.h"
#include "M_Path.h"
#include "M_Sprite.h"
#include "M_ProceduralSprite.h"
#include "M_Animation.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

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

	MINTY_API Font* resources_load_font(std::string const& path, int const size)
	{
		return TTF_OpenFont(path_combine(RESOURCES_DIRECTORY, path).c_str(), size);
	}

	MINTY_API Music* resources_load_music(std::string const& path)
	{
		Mix_Music* m = Mix_LoadMUS(path_combine(RESOURCES_DIRECTORY, path).c_str());

		// if did not load...
		if (!m)
		{
			Debug::logErrorSDL(35, std::format("Failed to load music at path: \"{}\".", path));
			return nullptr;
		}

		return new Music(m);
	}

	MINTY_API Sound* resources_load_sound(std::string const& path)
	{
		Mix_Chunk* m = Mix_LoadWAV(path_combine(RESOURCES_DIRECTORY, path).c_str());

		// if did not load...
		if (!m)
		{
			Debug::logErrorSDL(36, std::format("Failed to load sound at path: \"{}\".", path));
			return nullptr;
		}

		return new Sound(m);
	}

	SDL_Surface* resources_load_image(std::string const& path)
	{
		SDL_Surface* surface = IMG_Load(path_combine(RESOURCES_DIRECTORY, path).c_str());

		// if did not load...
		if (!surface)
		{
			Debug::logErrorSDL(7, std::format("Could not load image at path \"{0}\".", path));
		}

		return surface;
	}

	Sprite* resources_load_sprite(std::string const& path, SDL_Renderer* const renderer, PointF const& pivot)
	{
		// get the surface, use it to create a texture for the sprite, free the surface, return the sprite

		SDL_Surface* surface = resources_load_image(path);
		Sprite* sprite = new Sprite(surface, renderer);
		sprite->setPivot(pivot);
		return sprite;
	}

	MINTY_API ProceduralSprite* resources_load_proceduralSprite(std::string const& path, std::vector<std::string> const& artsPaths, SDL_Renderer* const renderer, PointF const& pivot)
	{
		// load main sprite
		Sprite* design = resources_load_sprite(path, renderer, pivot);

		// load art
		Sprite** arts = new Sprite * [artsPaths.size()];
		for (size_t i = 0; i < artsPaths.size(); i++)
		{
			arts[i] = resources_load_sprite(artsPaths[i], renderer, pivot);
		}

		// compile
		ProceduralSprite* sprite = new ProceduralSprite(design, arts, artsPaths.size());

		// delete design, but keep arts, those are being used
		delete design;

		return sprite;
	}

	Animation* resources_load_animation_single(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, PointF const& pivot)
	{
		// get sprite, turn it into an animation
		Sprite* sprite = resources_load_sprite(path, renderer); // pivot does not matter here

		Animation* animation = Animation::fromSprite_single(sprite, renderer, tileWidth, tileHeight, frameTime, looping);

		// no longer need original sprite
		delete sprite;

		return animation;
	}

	MINTY_API std::vector<Animation*> resources_load_animation_multiple(std::string const& path, SDL_Renderer* const renderer, int const tileWidth, int const tileHeight, elapsed_t const frameTime, bool const looping, std::vector<size_t> const& framesPerAnimation, PointF const& pivot)
	{
		// get sprite, turn it into an animation
		Sprite* sprite = resources_load_sprite(path, renderer); // pivot does not matter here

		std::vector<Animation*> animations = Animation::fromSprite_multiple(sprite, renderer, tileWidth, tileHeight, frameTime, looping, framesPerAnimation);

		// no longer need original sprite
		delete sprite;

		return animations;
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
	
	MINTY_API std::vector<Sprite*>* resources_load_all_sprites(std::string const& path, std::string const& extension, SDL_Renderer* const renderer, PointF const& pivot)
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
			sprites->push_back(resources_load_sprite(finalPath, renderer, pivot));

			i++;

			// get next path
			finalPath = basePath + std::to_string(i) + extension;
		}

		return sprites;
	}
}
