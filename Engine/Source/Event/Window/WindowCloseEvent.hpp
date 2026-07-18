#pragma once

/**
 * @file WindowCloseEvent.h
 * @brief Header file defining the WindowCloseEvent class.
 * @author Mitchell Talyat
 */

#include "Event/Event/Event.hpp"

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
		inline EventType get_type() const override { return EventTypeEnum::WindowClose; }

#pragma endregion
	};
}
