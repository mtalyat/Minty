#pragma once

/**
 * @file GamepadDisconnectEvent.h
 * @brief Header file defining the GamepadDisconnectEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.hpp"

namespace Minty
{
	/**
	 * @brief A GamepadDisconnectEvent is triggered when a gamepad is disconnected.
	 */
	class GamepadDisconnectEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GamepadDisconnectEvent.
		 * @param gamepadId The ID of the gamepad.
		 */
		GamepadDisconnectEvent(Index const gamepadId)
			: m_gamepadId(gamepadId)
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
		 * @brief Gets the type of this Event.
		 * @return GamepadDisconnect.
		 */
		inline EventType get_type() const override { return EventTypeEnum::GamepadDisconnect; }

#pragma endregion

#pragma region Variables

	private:
		Index m_gamepadId;

#pragma endregion
	};
}
