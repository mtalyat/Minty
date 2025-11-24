#pragma once
#include "Minty/Event/Event.h"
#include "Minty/Input/Key.h"
#include "Minty/Input/KeyAction.h"
#include "Minty/Input/KeyModifiers.h"

namespace Minty
{
	/// <summary>
	/// An Event that is triggered when a key is pressed or released.
	/// </summary>
	class KeyEvent
		: public Event
	{
#pragma region Variables

	private:
		Key m_key;
		KeyAction m_action;
		KeyModifiers m_modifiers;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new KeyEvent.
		/// </summary>
		/// <param name="key">The Key.</param>
		/// <param name="action">The KeyAction.</param>
		/// <param name="modifiers">The KeyModifiers.</param>
		KeyEvent(Key const key, KeyAction const action, KeyModifiers const modifiers)
			: m_key(key), m_action(action), m_modifiers(modifiers)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the key of this Event.
		/// </summary>
		/// <returns>The Key.</returns>
		Key get_key() const { return m_key; }

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
		/// <returns>Key.</returns>
		constexpr EventType get_type() const override { return EventType::Key; }

#pragma endregion

	};
}