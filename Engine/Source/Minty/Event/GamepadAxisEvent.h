#ifndef MINTY_EVENT_GAMEPADAXISEVENT_H
#define MINTY_EVENT_GAMEPADAXISEVENT_H

/**
 * @file GamepadAxisEvent.h
 * @brief Header file defining the GamepadAxisEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"
#include "Minty/Input/GamepadAxis.h"
#include "Minty/Input/KeyAction.h"

namespace Minty
{
	/**
	 * @brief A GamepadAxisEvent is triggered when a gamepad button is pressed or released.
	 */
	class GamepadAxisEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GamepadAxisEvent.
		 * @param gamepadId The ID of the gamepad.
		 * @param axis The axis that was changed.
		 * @param value The value of the axis.
		 */
		GamepadAxisEvent(Int const gamepadId, GamepadAxis const axis, Float const value)
			: m_gamepadId(gamepadId)
			, m_axis(axis)
			, m_value(value)
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
		 * @brief Gets the axis for this Event.
		 * @return The axis.
		 */
		inline GamepadAxis get_axis() const { return m_axis; }

		/**
		 * @brief Gets the value for this Event.
		 * @return The value.
		 */
		inline Float get_value() const { return m_value; }

		/**
		 * @brief Gets the type of this Event.
		 * @return GamepadAxis.
		 */
		inline EventType get_type() const override { return EventType::GamepadAxis; }

#pragma endregion

#pragma region Variables

	private:
		Int m_gamepadId;
		GamepadAxis m_axis;
		Float m_value;

#pragma endregion
	};
}

#endif // MINTY_EVENT_GAMEPADAXISEVENT_H