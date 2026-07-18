#pragma once

/**
 * @file KeyEvent.h
 * @brief Header file defining the KeyEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.hpp"
#include "Input/Key/Key.hpp"
#include "Input/Key/KeyAction.hpp"
#include "Input/Key/KeyModifier.hpp"

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
		 * @param modifiers The KeyModifierFlagsEnum.
		 */
		KeyEvent(Key const key, KeyAction const action, KeyModifier const modifiers)
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
		 * @return The KeyModifier.
		 */
		inline KeyModifier get_modifier() const { return m_modifiers; }

		/**
		 * @brief Gets the type of this Event.
		 * @return Key.
		 */
		inline EventType get_type() const override { return EventTypeEnum::Key; }

#pragma endregion

#pragma region Variables

	private:
		Key m_key;
		KeyAction m_action;
		KeyModifier m_modifiers;

#pragma endregion
	};
}
