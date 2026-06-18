#pragma once

/**
 * @file GamepadConnectEvent.h
 * @brief Header file defining the GamepadConnectEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.h"

namespace Minty
{
	/**
	 * @brief A GamepadConnectEvent is triggered when a gamepad is connected.
	 */
	class GamepadConnectEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GamepadConnectEvent.
		 * @param gamepadId The ID of the gamepad.
		 */
		GamepadConnectEvent(Index const gamepadId)
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
		 * @return GamepadConnect.
		 */
		inline EventType get_type() const override { return EventTypeEnum::GamepadConnect; }

#pragma endregion

#pragma region Variables

	private:
		Index m_gamepadId;

#pragma endregion
	};
}
