#pragma once
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// A GamepadDisconnectEvent is triggered when a gamepad is disconnected.
	/// </summary>
	class GamepadDisconnectEvent
		: public Event
	{
#pragma region Variables

	private:
		Int m_gamepadId;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new GamepadDisconnectEvent.
		/// </summary>
		/// <param name="gamepadId">The ID of the gamepad.</param>
		GamepadDisconnectEvent(Int const gamepadId)
			: m_gamepadId(gamepadId)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the ID of the gamepad for this Event.
		/// </summary>
		/// <returns>The ID.</returns>
		Int get_id() const { return m_gamepadId; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>GamepadDisconnect.</returns>
		constexpr EventType get_type() const override { return EventType::GamepadDisconnect; }

#pragma endregion

	};
}