#pragma once
#include "Minty/Event/Event.h"
#include "Minty/Input/GamepadAxis.h"
#include "Minty/Input/KeyAction.h"

namespace Minty
{
	/// <summary>
	/// A GamepadAxisEvent is triggered when a gamepad button is pressed or released.
	/// </summary>
	class GamepadAxisEvent
		: public Event
	{
#pragma region Variables

	private:
		Int m_gamepadId;
		GamepadAxis m_axis;
		Float m_value;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new GamepadAxisEvent.
		/// </summary>
		/// <param name="gamepadId">The ID of the gamepad.</param>
		/// <param name="axis">The axis that was changed.</param>
		/// <param name="action">The action of the button.</param>
		GamepadAxisEvent(Int const gamepadId, GamepadAxis const axis, Float const value)
			: m_gamepadId(gamepadId)
			, m_axis(axis)
			, m_value(value)
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
		/// Gets the axis for this Event.
		/// </summary>
		/// <returns>The axis.</returns>
		GamepadAxis get_axis() const { return m_axis; }

		/// <summary>
		/// Gets the value for this Event.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_value() const { return m_value; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>GamepadAxis.</returns>
		constexpr EventType get_type() const override { return EventType::GamepadAxis; }

#pragma endregion
	};
}