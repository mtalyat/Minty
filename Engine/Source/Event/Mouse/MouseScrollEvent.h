#pragma once

/**
 * @file MouseScrollEvent.h
 * @brief Header file defining the MouseScrollEvent class.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float2.h"
#include "Event/Event/Event.h"

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
		 * @param offset The offset of the mouse.
		 */
		MouseScrollEvent(Float2 const offset)
			: m_offset(offset)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the offset of this Event.
		 * @return The offset.
		 */
		inline Float2 get_offset() const { return m_offset; }

		/**
		 * @brief Gets the type of this Event.
		 * @return MouseScroll.
		 */
		inline EventType get_type() const override { return EventTypeEnum::MouseScroll; }

#pragma endregion

#pragma region Variables

	private:
		Float2 m_offset;

#pragma endregion
	};
}
