#pragma once

/**
 * @file GamepadButtonEvent.h
 * @brief Header file defining the GamepadButtonEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.hpp"
#include "Input/Gamepad/GamepadButton.hpp"
#include "Input/Gamepad/GamepadAction.hpp"

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
		GamepadButtonEvent(Index const gamepadId, GamepadButton const button, GamepadAction const action)
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
		inline Index get_id() const { return m_gamepadId; }

		/**
		 * @brief Gets the button for this Event.
		 * @return The button.
		 */
		inline GamepadButton get_button() const { return m_button; }

		/**
		 * @brief Gets the action for this Event.
		 * @return The action.
		 */
		inline GamepadAction get_action() const { return m_action; }

		/**
		 * @brief Gets the type of this Event.
		 * @return GamepadButton.
		 */
		inline EventType get_type() const override { return EventTypeEnum::GamepadButton; }

#pragma endregion

#pragma region Variables

	private:
		Index m_gamepadId;
		GamepadButton m_button;
		GamepadAction m_action;

#pragma endregion
	};
}
