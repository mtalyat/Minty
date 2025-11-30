#ifndef MINTY_EVENT_GAMEPADBUTTONEVENT_H
#define MINTY_EVENT_GAMEPADBUTTONEVENT_H

/**
 * @file GamepadButtonEvent.h
 * @brief Header file defining the GamepadButtonEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"
#include "Minty/Input/GamepadButton.h"
#include "Minty/Input/KeyAction.h"

namespace Minty
{
	/**
	 * @brief A GamepadButtonEvent is triggered when a gamepad button is pressed or released.
	 */
	class GamepadButtonEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GamepadButtonEvent.
		 * @param gamepadId The ID of the gamepad.
		 * @param button The button that was pressed or released.
		 * @param action The action of the button.
		 */
		GamepadButtonEvent(Int const gamepadId, GamepadButton const button, KeyAction const action)
			: m_gamepadId(gamepadId)
			, m_button(button)
			, m_action(action)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the ID of the gamepad for this Event.
		 * @return The ID.
		 */
		inline Int get_id() const { return m_gamepadId; }

		/**
		 * @brief Gets the button for this Event.
		 * @return The button.
		 */
		inline GamepadButton get_button() const { return m_button; }

		/**
		 * @brief Gets the action for this Event.
		 * @return The action.
		 */
		inline KeyAction get_action() const { return m_action; }

		/**
		 * @brief Gets the type of this Event.
		 * @return GamepadButton.
		 */
		inline EventType get_type() const override { return EventType::GamepadButton; }

#pragma endregion

#pragma region Variables

	private:
		Int m_gamepadId;
		GamepadButton m_button;
		KeyAction m_action;

#pragma endregion
	};
}

#endif // MINTY_EVENT_GAMEPADBUTTONEVENT_H