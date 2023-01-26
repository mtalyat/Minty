#include "pch.h"
#include "M_InputMap.h"

namespace minty
{
	InputMap::InputMap(std::string const& name)
		: m_name(name)
		, mp_keyDownEvents(new std::map<SDL_Keycode, Event<>>())
		, mp_keyUpEvents(new std::map<SDL_Keycode, Event<>>())
		, mp_mouseDownEvents(new std::map<Uint8, Event<SDL_MouseButtonEvent*>>())
		, mp_mouseUpEvents(new std::map<Uint8, Event<SDL_MouseButtonEvent*>>())
		, mp_mouseMoveEvent(new Event<SDL_MouseMotionEvent*>())
		, mp_mouseScrollEvent(new Event<SDL_MouseWheelEvent*>())
	{}

	InputMap::~InputMap()
	{
		// delete members
		delete mp_keyDownEvents;
		delete mp_keyUpEvents;
		delete mp_mouseDownEvents;
		delete mp_mouseUpEvents;
		delete mp_mouseMoveEvent;
		delete mp_mouseScrollEvent;
	}

	inline void minty::InputMap::onKeyDown(SDL_Keycode const key)
	{
		auto action = mp_keyDownEvents->find(key);

		if (action != mp_keyDownEvents->end())
		{
			action->second.invoke();
		}
	}

	inline void InputMap::onKeyUp(SDL_Keycode const key)
	{
		auto action = mp_keyUpEvents->find(key);

		if (action != mp_keyUpEvents->end())
		{
			action->second.invoke();
		}
	}

	inline void InputMap::onMouseDown(SDL_MouseButtonEvent* const button)
	{
		auto action = mp_mouseDownEvents->find(button->button);

		if (action != mp_mouseDownEvents->end())
		{
			// event found
			action->second.invoke(button);
		}
	}

	inline void InputMap::onMouseUp(SDL_MouseButtonEvent* const button)
	{
		auto action = mp_mouseUpEvents->find(button->button);

		if (action != mp_mouseUpEvents->end())
		{
			// event found
			action->second.invoke(button);
		}
	}

	inline void InputMap::onMouseMove(SDL_MouseMotionEvent* const button)
	{
		mp_mouseMoveEvent->invoke(button);
	}

	inline void InputMap::onMouseScroll(SDL_MouseWheelEvent* const scroll)
	{
		mp_mouseScrollEvent->invoke(scroll);
	}

	inline void InputMap::emplace_key_down(SDL_Keycode const key, std::function<void()> const& action)
	{
		(*mp_keyDownEvents)[key].emplace(action);
	}

	inline void InputMap::emplace_key_up(SDL_Keycode const key, std::function<void()> const& action)
	{
		(*mp_keyUpEvents)[key].emplace(action);
	}

	inline void InputMap::emplace_key(SDL_Keycode const key, std::function<void()> const& downAction, std::function<void()> const& upAction)
	{
		emplace_key_down(key, downAction);
		emplace_key_up(key, upAction);
	}

	inline void InputMap::emplace_mouse_down(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& action)
	{
		(*mp_mouseDownEvents)[button].emplace(action);
	}

	inline void InputMap::emplace_mouse_up(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& action)
	{
		(*mp_mouseUpEvents)[button].emplace(action);
	}

	inline void InputMap::emplace_mouse(Uint8 const button, std::function<void(SDL_MouseButtonEvent*)> const& downAction, std::function<void(SDL_MouseButtonEvent*)> const& upAction)
	{
		emplace_mouse_down(button, downAction);
		emplace_mouse_up(button, upAction);
	}

	inline void InputMap::emplace_mouse_move(std::function<void(SDL_MouseMotionEvent*)> const& action)
	{
		mp_mouseMoveEvent->emplace(action);
	}

	inline void InputMap::emplace_mouse_scroll(std::function<void(SDL_MouseWheelEvent*)> const& action)
	{
		mp_mouseScrollEvent->emplace(action);
	}
}
