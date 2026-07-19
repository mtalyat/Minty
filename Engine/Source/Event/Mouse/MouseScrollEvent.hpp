#pragma once

/**
 * @file MouseScrollEvent.hpp
 * @brief Header file defining the MouseScrollEvent class.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float2.hpp"
#include "Event/Event/Event.hpp"

namespace Minty
{
	/**
	 * @brief A MouseScrollEvent is triggered when the mouse is scrolled.
	 */
	class MouseScrollEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new MouseScrollEvent.
		 * @param scroll The offset of the mouse.
		 */
		MouseScrollEvent(Float2 const scroll)
			: m_scroll(scroll)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the offset of this Event.
		 * @return The offset.
		 */
		inline Float2 get_scroll() const { return m_scroll; }

		/**
		 * @brief Gets the type of this Event.
		 * @return MouseScroll.
		 */
		inline EventType get_type() const override { return EventTypeEnum::MouseScroll; }

#pragma endregion

#pragma region Variables

	private:
		Float2 m_scroll;

#pragma endregion
	};
}
