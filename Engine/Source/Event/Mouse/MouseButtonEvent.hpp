#pragma once

/**
 * @file MouseButtonEvent.h
 * @brief Header file defining the MouseButtonEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "Input/Mouse/MouseAction.hpp"
#include "Input/Key/KeyModifier.hpp"

namespace Minty
{
	/**
	 * @brief A MouseButtonEvent is triggered when a MouseButton is pressed or released.
	 */
	class MouseButtonEvent
		: public Event
	{
#pragma region Constructors
		
	public:
		/**
		 * @brief Creates a new MouseButtonEvent.
		 * @param button The MouseButton.
		 * @param action The KeyAction.
		 * @param modifiers The KeyModifier.
		 */
		MouseButtonEvent(MouseButton const button, KeyAction const action, KeyModifier const modifiers)
			: m_button(button), m_action(action), m_modifiers(modifiers)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the button of this Event.
		 * @return The MouseButton.
		 */
		inline MouseButton get_button() const { return m_button; }

		/**
		 * @brief Gets the action of this Event.
		 * @return The KeyAction.
		 */
		inline KeyAction get_action() const { return m_action; }

		/**
		 * @brief Gets the modifiers of this Event.
		 * @return The KeyModifier.
		 */
		inline KeyModifier get_modifiers() const { return m_modifiers; }

		/**
		 * @brief Gets the type of this Event.
		 * @return MouseButton.
		 */
		inline EventType get_type() const override { return EventTypeEnum::MouseButton; }

#pragma endregion

#pragma region Variables

	private:
		MouseButton m_button;
		KeyAction m_action;
		KeyModifier m_modifiers;

#pragma endregion
	};
}
