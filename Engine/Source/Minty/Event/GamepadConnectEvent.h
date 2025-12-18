#ifndef MINTY_EVENT_GAMEPADCONNECTEVENT_H
#define MINTY_EVENT_GAMEPADCONNECTEVENT_H

/**
 * @file GamepadConnectEvent.h
 * @brief Header file defining the GamepadConnectEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"

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
		GamepadConnectEvent(Int const gamepadId)
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
		inline Int get_id() const { return m_gamepadId; }

		/**
		 * @brief Gets the type of this Event.
		 * @return GamepadConnect.
		 */
		inline EventType get_type() const override { return EventType::GamepadConnect; }

#pragma endregion

#pragma region Variables

	private:
		Int m_gamepadId;

#pragma endregion
	};
}

#endif // MINTY_EVENT_GAMEPADCONNECTEVENT_H