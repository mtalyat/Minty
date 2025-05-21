#pragma once
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// A GamepadConnectEvent is triggered when a gamepad is connected.
	/// </summary>
	class GamepadConnectEvent
		: public Event
	{
#pragma region Variables

	private:
		Int m_gamepadId;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new GamepadConnectEvent.
		/// </summary>
		/// <param name="gamepadId">The ID of the gamepad.</param>
		GamepadConnectEvent(Int const gamepadId)
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
		/// <returns>GamepadConnect.</returns>
		constexpr EventType get_type() const override { return EventType::GamepadConnect; }

#pragma endregion

	};
}