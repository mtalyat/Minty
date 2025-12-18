#ifndef MINTY_EVENT_WINDOWRESIZEEVENT_H
#define MINTY_EVENT_WINDOWRESIZEEVENT_H

/**
 * @file WindowResizeEvent.h
 * @brief Header file defining the WindowResizeEvent class.
 * @author Mitchell Talyat
 */

#include "Minty/Event/Event.h"

namespace Minty
{
	/**
	 * @brief Holds data about a WindowResizeEvent.
	 */
	class WindowResizeEvent
		: public Event
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new WindowResizeEvent.
		 * @param width The new width.
		 * @param height The new height.
		 */
		WindowResizeEvent(UInt width, UInt height)
			: m_width(width), m_height(height)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the new width of the Window.
		 * @return The new width.
		 */
		inline UInt get_width() const { return m_width; }

		/**
		 * @brief Gets the new height of the Window.
		 * @return The new height.
		 */
		inline UInt get_height() const { return m_height; }

		/**
		 * @brief Gets the type of this Event.
		 * @return WindowResize.
		 */
		inline EventType get_type() const override { return EventType::WindowResize; }

#pragma endregion

#pragma region Variables

	private:
		UInt m_width;
		UInt m_height;

#pragma endregion
	};
}

#endif // MINTY_EVENT_WINDOWRESIZEEVENT_H