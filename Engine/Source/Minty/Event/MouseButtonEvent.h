#pragma once
#include "Minty/Event/Event.h"
#include "Minty/Input/MouseButton.h"
#include "Minty/Input/KeyAction.h"
#include "Minty/Input/KeyModifiers.h"

namespace Minty
{
	/// <summary>
	/// A MouseButtonEvent is triggered when a MouseButton is pressed or released.
	/// </summary>
	class MouseButtonEvent
		: public Event
	{
#pragma region Variables

	private:
		MouseButton m_button;
		KeyAction m_action;
		KeyModifiers m_modifiers;

#pragma endregion

#pragma region Constructors
		
	public:
		/// <summary>
		/// Creates a new MouseButtonEvent.
		/// </summary>
		/// <param name="button">The MouseButton.</param>
		/// <param name="action">The KeyAction.</param>
		/// <param name="modifiers">The KeyModifiers.</param>
		MouseButtonEvent(MouseButton const button, KeyAction const action, KeyModifiers const modifiers)
			: m_button(button), m_action(action), m_modifiers(modifiers)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the button of this Event.
		/// </summary>
		/// <returns>The MouseButton.</returns>
		MouseButton get_button() const { return m_button; }

		/// <summary>
		/// Gets the action of this Event.
		/// </summary>
		/// <returns>The KeyAction.</returns>
		KeyAction get_action() const { return m_action; }

		/// <summary>
		/// Gets the modifiers of this Event.
		/// </summary>
		/// <returns>The KeyModifiers.</returns>
		KeyModifiers get_modifiers() const { return m_modifiers; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>MouseButton.</returns>
		constexpr EventType get_type() const override { return EventType::MouseButton; }

#pragma endregion
	};
}