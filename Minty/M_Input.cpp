#include "pch.h"
#include "M_Input.h"
#include "M_Pair.h"
#include "M_Debug.h"
#include "M_Screen.h"
#include <SDL.h>

namespace minty
{
	inline Input::Input()
		: mp_inputMaps(new std::map<std::string, InputMap*>())
		, mp_downKeys(new std::unordered_set<SDL_Keycode>())
		, mp_downMice(new std::unordered_set<Uint8>())
		, mp_activeMap(nullptr)
	{}

	inline Input::~Input()
	{
		// delete maps in list
		for (auto const& pair : *mp_inputMaps)
		{
			delete pair.second;
		}

		// delete members
		delete mp_inputMaps;
		delete mp_downKeys;
		delete mp_downMice;
	}

	Point Input::getMousePositionRaw() const
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return Point(x, y);
	}

	Point Input::getMousePosition(Screen const* const screen) const
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		int w, h;
		SDL_GetWindowSize(screen->window(), &w, &h);
		return Point(static_cast<float>(x) / static_cast<float>(w) * static_cast<float>(screen->width),
			static_cast<float>(y) / static_cast<float>(h) * static_cast<float>(screen->height));
	}

	inline bool Input::isKeyDown(SDL_Keycode const key) const
	{
		return mp_downKeys->contains(key);
	}

	inline bool Input::isMouseDown(Uint8 const mouse) const
	{
		return mp_downMice->contains(mouse);
	}

	inline void Input::onKeyDown(SDL_Keycode const key)
	{
		// only emit event if key is not already down
		if (mp_downKeys->emplace(key).second)
		{
			// the key was inserted, so it is a new down
			// call event
			if (mp_activeMap)
			{
				mp_activeMap->onKeyDown(key);
			}
		}
	}

	inline void Input::onKeyUp(SDL_Keycode const key)
	{
		// remove key from downs
		mp_downKeys->erase(key);

		if (mp_activeMap)
		{
			// call event
			mp_activeMap->onKeyUp(key);
		}
	}

	inline void Input::onMouseDown(SDL_MouseButtonEvent* const button)
	{
		mp_downMice->emplace(button->button);

		if (mp_activeMap)
		{
			mp_activeMap->onMouseDown(button);
		}
	}

	inline void Input::onMouseUp(SDL_MouseButtonEvent* const button)
	{
		mp_downMice->erase(button->button);

		if (mp_activeMap)
		{
			mp_activeMap->onMouseUp(button);
		}
	}

	inline void Input::onMouseMove(SDL_MouseMotionEvent* const button)
	{
		if (mp_activeMap)
		{
			mp_activeMap->onMouseMove(button);
		}
	}

	inline void Input::onMouseScroll(SDL_MouseWheelEvent* const scroll)
	{
		if (mp_activeMap)
		{
			mp_activeMap->onMouseScroll(scroll);
		}
	}

	inline void Input::emplace(InputMap* const map)
	{
		if (!mp_inputMaps->emplace(map->name(), map).second)
		{
			// value already exists
			delete map;
		}

		// if only map value, select it
		if (mp_inputMaps->size() == 1)
		{
			select(map->name());
		}
	}

	inline void Input::select(std::string const& name)
	{
		auto map = mp_inputMaps->find(name);

		if (map != mp_inputMaps->end())
		{
			mp_activeMap = map->second;
		}
		else
		{
			Debug::logError(19, std::format("Could not find input map \"{0}\".", name));
		}
	}
}
