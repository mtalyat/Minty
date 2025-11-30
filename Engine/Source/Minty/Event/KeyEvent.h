#ifndef MINTY_EVENT_KEYEVENT_H
#define MINTY_EVENT_KEYEVENT_H

/**
 * @file KeyEvent.h
 * @brief Header file defining the KeyEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"
#include "Minty/Input/Key.h"
#include "Minty/Input/KeyAction.h"
#include "Minty/Input/KeyModifiers.h"

namespace Minty
{
	/**
	 * @brief An Event that is triggered when a key is pressed or released.
	 */
	class KeyEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new KeyEvent.
		 * @param key The Key.
		 * @param action The KeyAction.
		 * @param modifiers The KeyModifiers.
		 */
		KeyEvent(Key const key, KeyAction const action, KeyModifiers const modifiers)
			: m_key(key), m_action(action), m_modifiers(modifiers)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the key of this Event.
		 * @return The Key.
		 */
		inline Key get_key() const { return m_key; }

		/**
		 * @brief Gets the action of this Event.
		 * @return The KeyAction.
		 */
		inline KeyAction get_action() const { return m_action; }

		/**
		 * @brief Gets the modifiers of this Event.
		 * @return The KeyModifiers.
		 */
		inline KeyModifiers get_modifiers() const { return m_modifiers; }

		/**
		 * @brief Gets the type of this Event.
		 * @return Key.
		 */
		inline EventType get_type() const override { return EventType::Key; }

#pragma endregion

#pragma region Variables

	private:
		Key m_key;
		KeyAction m_action;
		KeyModifiers m_modifiers;

#pragma endregion
	};
}

#endif // MINTY_EVENT_KEYEVENT_H