#pragma once
#include "Minty/Event/Event.h"
#include "Minty/Input/GamepadButton.h"
#include "Minty/Input/KeyAction.h"

namespace Minty
{
	/// <summary>
	/// A GamepadButtonEvent is triggered when a gamepad button is pressed or released.
	/// </summary>
	class GamepadButtonEvent
		: public Event
	{
#pragma region Variables

	private:
		Int m_gamepadId;
		GamepadButton m_button;
		KeyAction m_action;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new GamepadButtonEvent.
		/// </summary>
		/// <param name="gamepadId">The ID of the gamepad.</param>
		/// <param name="button">The button that was pressed or released.</param>
		/// <param name="action">The action of the button.</param>
		GamepadButtonEvent(Int const gamepadId, GamepadButton const button, KeyAction const action)
			: m_gamepadId(gamepadId)
			, m_button(button)
			, m_action(action)
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
		/// Gets the button for this Event.
		/// </summary>
		/// <returns>The button.</returns>
		GamepadButton get_button() const { return m_button; }

		/// <summary>
		/// Gets the action for this Event.
		/// </summary>
		/// <returns>The action.</returns>
		KeyAction get_action() const { return m_action; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>GamepadButton.</returns>
		constexpr EventType get_type() const override { return EventType::GamepadButton; }

#pragma endregion
	};
}