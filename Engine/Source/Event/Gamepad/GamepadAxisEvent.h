#pragma once

/**
 * @file GamepadAxisEvent.h
 * @brief Header file defining the GamepadAxisEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.h"
#include "Input/Gamepad/GamepadAxis.h"

namespace Minty
{
	/**
	 * @brief A GamepadAxisEvent is triggered when a gamepad axis is moved.
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
		GamepadAxisEvent(Index const gamepadId, GamepadAxis const axis, Float const value)
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
		inline Index get_id() const { return m_gamepadId; }

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
		inline EventType get_type() const override { return EventTypeEnum::GamepadAxis; }

#pragma endregion

#pragma region Variables

	private:
		Index m_gamepadId;
		GamepadAxis m_axis;
		Float m_value;

#pragma endregion
	};
}
