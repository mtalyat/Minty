#ifndef MINTY_EVENT_EVENT_H
#define MINTY_EVENT_EVENT_H

/**
 * @file Event.h
 * @brief Header file defining the base Event class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Event/EventState.h"
#include "Minty/Event/EventType.h"

namespace Minty
{
	/**
	 * @brief The base class for all events.
	 */
	class Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Event.
		 */
		Event()
			: m_state(EventState::Unhandled)
		{
		}

		virtual ~Event() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the state of this Event.
		 * @return The EventState.
		 */
		inline EventState get_state() const { return m_state; }

		/**
		 * @brief Sets the state of this Event.
		 * @param state The new EventState.
		 */
		inline void set_state(EventState const state)
		{
			MINTY_ASSERT(state != EventState::Unhandled, ErrorCode::Argument_ExpectedNonDefault);
			m_state = state;
		}

		/**
		 * @brief Checks if this Event is processed. A processed Event is one that has been handled or canceled.
		 * @return True if not Unhandled.
		 */
		inline Bool is_processed() const { return m_state != EventState::Unhandled; }

		/**
		 * @brief Gets the type of this Event.
		 * @return The EventType.
		 */
		virtual EventType get_type() const = 0;

#pragma endregion

#pragma region Variables

	private:
		EventState m_state;

#pragma endregion
	};
}

#endif // MINTY_EVENT_EVENT_H