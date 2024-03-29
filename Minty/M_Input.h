#pragma once

#include "M_Object.h"
#include "M_InputMap.h"
#include "M_Point.h"
#include <SDL.h>
#include <map>
#include <unordered_set>

namespace minty
{
	class Screen;

	/// <summary>
	/// Handles all of the inputs (keyboard, mouse, etc.) provided by SDL.
	/// </summary>
	class MINTY_API Input
		: public Object
	{
	private:
		// the input maps
		std::map<std::string, InputMap*>* mp_inputMaps;
		// the keys currently being pressed down
		std::unordered_set<SDL_Keycode>* mp_downKeys;
		// the mouse buttons currently being pressed down
		std::unordered_set<Uint8>* mp_downMice;
		// the active input map being used
		InputMap* mp_activeMap;

	public:
		/// <summary>
		/// Creates an empty Input system.
		/// </summary>
		Input();

		~Input();

		/// <summary>
		/// Gets the mouse position of the cursor, relative to the window.
		/// </summary>
		/// <returns></returns>
		Point getMousePositionRaw() const;

		/// <summary>
		/// Gets the mouse position of the cursor, relative to the screen.
		/// </summary>
		/// <returns></returns>
		Point getMousePosition(Screen const* const screen) const;

		/// <summary>
		/// Checks if the given key is currently being held down.
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool isKeyDown(SDL_Keycode const key) const;

		/// <summary>
		/// Checks if the given mouse button is currently being held down.
		/// </summary>
		/// <param name="mouse"></param>
		/// <returns></returns>
		bool isMouseDown(Uint8 const mouse) const;

		/// <summary>
		/// Triggers the key down event for the given key on the active input map.
		/// </summary>
		/// <param name="key"></param>
		void onKeyDown(SDL_Keycode const key);

		/// <summary>
		/// Triggers the key up event for the given key on the active input map.
		/// </summary>
		/// <param name="key"></param>
		void onKeyUp(SDL_Keycode const key);

		/// <summary>
		/// Triggers the mouse down event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseDown(SDL_MouseButtonEvent* const button);

		/// <summary>
		/// Triggers the mouse up event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseUp(SDL_MouseButtonEvent* const button);

		/// <summary>
		/// Triggers the mouse move event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseMove(SDL_MouseMotionEvent* const button);

		/// <summary>
		/// Triggers the mouse scroll event.
		/// </summary>
		/// <param name="scroll"></param>
		void onMouseScroll(SDL_MouseWheelEvent* const scroll);

		/// <summary>
		/// Adds an InputMap to the Input system.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="map"></param>
		void emplace(InputMap* const map);

		/// <summary>
		/// Sets the active InputMap to the corresponding InputMap from the given name.
		/// </summary>
		/// <param name="name"></param>
		void select(std::string const& name);
	};
}