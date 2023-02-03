#pragma once

#include "M_Object.h"
#include "M_Event.h"
#include "M_Point.h"
#include <SDL.h>
#include <map>

namespace minty
{
	/// <summary>
	/// Holds a map of inputs that will be invoked when SDL triggers them.
	/// </summary>
	class MINTY_API InputMap
		: public Object
	{
	private:
		std::string m_name;

		std::map<SDL_Keycode, Event<>>* mp_keyDownEvents;
		std::map<SDL_Keycode, Event<>>* mp_keyUpEvents;
		std::map<Uint8, Event<SDL_MouseButtonEvent*>>* mp_mouseDownEvents;
		std::map<Uint8, Event<SDL_MouseButtonEvent*>>* mp_mouseUpEvents;
		Event<SDL_MouseMotionEvent*>* mp_mouseMoveEvent;
		Event<SDL_MouseWheelEvent*>* mp_mouseScrollEvent;

	public:
		/// <summary>
		/// Creates a blank Input Map.
		/// </summary>
		InputMap(std::string const& name);

		~InputMap();

		std::string const& name() const { return m_name; }

#pragma region Events

		/// <summary>
		/// Triggers the key down Event for the given key.
		/// </summary>
		/// <param name="key"></param>
		void onKeyDown(SDL_Keycode const key);

		/// <summary>
		/// Triggers the key up Event for the given key.
		/// </summary>
		/// <param name="key"></param>
		void onKeyUp(SDL_Keycode const key);

		/// <summary>
		/// Triggers the mouse down Event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseDown(SDL_MouseButtonEvent* const button);

		/// <summary>
		/// Triggers the mouse up Event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseUp(SDL_MouseButtonEvent* const button);

		/// <summary>
		/// Triggers the mouse move Event.
		/// </summary>
		/// <param name="button"></param>
		void onMouseMove(SDL_MouseMotionEvent* const button);

		/// <summary>
		/// Triggers the mouse scroll Event.
		/// </summary>
		/// <param name="scroll"></param>
		void onMouseScroll(SDL_MouseWheelEvent* const scroll);

#pragma endregion

#pragma region Emplacing

		/// <summary>
		/// Adds a function to the key down Event for the given key.
		/// </summary>
		/// <param name="key"></param>
		/// <param name="action"></param>
		inline void emplace_key_down(SDL_Keycode const key, std::function<void()> const& action);

		/// <summary>
		/// Adds a function to the key up Event for the given key.
		/// </summary>
		/// <param name="key"></param>
		/// <param name="action"></param>
		inline void emplace_key_up(SDL_Keycode const key, std::function<void()> const& action);

		/// <summary>
		/// Adds a down and an up function to the respective key Events for the given key.
		/// </summary>
		/// <param name="key"></param>
		/// <param name="downAction"></param>
		/// <param name="upAction"></param>
		void emplace_key(SDL_Keycode const key, std::function<void()> const& downAction, std::function<void()> const& upAction);

		/// <summary>
		/// Adds a function that is invoked when the mouse is pressed down.
		/// </summary>
		/// <param name="button"></param>
		/// <param name="action"></param>
		inline void emplace_mouse_down(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& action);

		/// <summary>
		/// Adds a function that is invoked when the mouse is released up.
		/// </summary>
		/// <param name="button"></param>
		/// <param name="action"></param>
		inline void emplace_mouse_up(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& action);

		/// <summary>
		/// Adds a function to when the mouse is pressed down, and another function when the mouse is released up.
		/// </summary>
		/// <param name="button"></param>
		/// <param name="downAction"></param>
		/// <param name="upAction"></param>
		void emplace_mouse(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& downAction, std::function<void(SDL_MouseButtonEvent*)> const& upAction);

		/// <summary>
		/// Adds a function that is invoked when the mouse moves.
		/// </summary>
		/// <param name="action"></param>
		inline void emplace_mouse_move(std::function<void(SDL_MouseMotionEvent*)> const& action);

		/// <summary>
		/// Adds a function that is invoked when the mouse scrolls.
		/// </summary>
		/// <param name="action"></param>
		inline void emplace_mouse_scroll(std::function<void(SDL_MouseWheelEvent*)> const& action);

#pragma endregion
	};
}