#include "pch.h"
#include "M_Screen.h"
#include "M_Debug.h"
#include "M_Resources.h"

namespace minty
{
	inline Screen::Screen(std::string const& title, int const w, int const h)
		: width(w), height(h), mp_window(nullptr), mp_renderer(nullptr), mp_background_texture(nullptr)
	{
		// create window with title
		if (!(mp_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL)))
		{
			Debug::logErrorSDL(00003, "Failed to create window.");
		}

		// create renderer for the window
		if (!(mp_renderer = SDL_CreateRenderer(mp_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)))
		{
			Debug::logErrorSDL(00004, "Failed to create renderer.");
		}

		// set icon
		SDL_Surface* icon = resources_load_image("Icon.png");
		if (!icon)
		{
			Debug::logErrorSDL(00005, "Failed to load icon.");
		}
		else
		{
			SDL_SetWindowIcon(mp_window, icon);
			SDL_FreeSurface(icon);
		}

		// make it resizable
		SDL_SetWindowResizable(mp_window, SDL_TRUE);

		// make it full screen
		SDL_SetWindowFullscreen(mp_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		// set the resolution the window should keep
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
		if (SDL_RenderSetLogicalSize(mp_renderer, width, height))
		{
			Debug::logErrorSDL(00006, "Failed to set logical renderer size.");
		}

		// support transparency
		SDL_SetRenderTarget(mp_renderer, NULL);
		SDL_SetRenderDrawBlendMode(mp_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(mp_renderer, 0, 0, 0, 0);
	}
	
	inline Screen::~Screen()
	{
		// clean up SDL resources
		SDL_DestroyTexture(mp_background_texture);
		SDL_DestroyRenderer(mp_renderer);
		SDL_DestroyWindow(mp_window);
	}
	
	inline Rect Screen::rect() const
	{
		return Rect(0, 0, width, height);
	}
	
	inline Point Screen::size() const
	{
		return Point(width, height);
	}

	inline std::string const Screen::toString() const { return std::format("({0}, {1})", width, height); }
}
