#pragma once

/**
 * @file MouseMoveEvent.h
 * @brief Header file defining the MouseMoveEvent class.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float2.h"
#include "Event/Event/Event.h"

namespace Minty
{
	/**
	 * @brief A MouseMoveEvent is triggered when the mouse is moved.
	 */
	class MouseMoveEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new MouseMoveEvent.
		 * @param position The position of the mouse.
		 */
		MouseMoveEvent(Float2 const position)
			: m_position(position)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the position of this Event.
		 * @return The position.
		 */
		inline Float2 get_position() const { return m_position; }

		/**
		 * @brief Gets the type of this Event.
		 * @return MouseMove.
		 */
		inline EventType get_type() const override { return EventTypeEnum::MouseMove; }

#pragma endregion

#pragma region Variables

	private:
		Float2 m_position;

#pragma endregion
	};
}
