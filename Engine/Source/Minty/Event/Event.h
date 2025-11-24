#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Event/EventState.h"
#include "Minty/Event/EventType.h"
#include <functional>

namespace Minty
{
	/// <summary>
	/// Holds data about an Event.
	/// </summary>
	class Event
	{
#pragma region Variables

	private:
		EventState m_state;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Event.
		/// </summary>
		Event()
			: m_state(EventState::Unhandled)
		{
		}

		virtual ~Event() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the state of this Event.
		/// </summary>
		/// <returns>The EventState.</returns>
		EventState get_state() const
		{
			return m_state;
		}

		/// <summary>
		/// Sets the state of this Event.
		/// </summary>
		/// <param name="state">The new EventState.</param>
		void set_state(EventState const state)
		{
			MINTY_ASSERT(state != EventState::Unhandled, "Cannot set state to Unhandled.");
			m_state = state;
		}

		/// <summary>
		/// Checks if this Event is processed. A processed Event is one that has been handled or canceled.
		/// </summary>
		/// <returns>True if not Unhandled.</returns>
		Bool is_processed() const { return m_state != EventState::Unhandled; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>The EventType.</returns>
		virtual constexpr EventType get_type() const = 0;

#pragma endregion
	};

	using EventCallbackFunction = Function<void(Event&)>;
}