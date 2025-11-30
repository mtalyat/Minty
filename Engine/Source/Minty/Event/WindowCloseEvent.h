#ifndef MINTY_EVENT_WINDOWCLOSEEVENT_H
#define MINTY_EVENT_WINDOWCLOSEEVENT_H

/**
 * @file WindowCloseEvent.h
 * @brief Header file defining the WindowCloseEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"

namespace Minty
{
	/**
	 * @brief Holds data about a WindowCloseEvent.
	 */
	class WindowCloseEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new WindowCloseEvent.
		 */
		WindowCloseEvent() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the type of this Event.
		 * @return WindowClose.
		 */
		inline EventType get_type() const override { return EventType::WindowClose; }

#pragma endregion
	};
}

#endif // MINTY_EVENT_WINDOWCLOSEEVENT_H