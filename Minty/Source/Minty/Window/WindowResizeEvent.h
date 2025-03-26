#pragma once
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// Holds data about a WindowResizeEvent.
	/// </summary>
	class WindowResizeEvent
		: public Event
	{
#pragma region Variables

	private:
		UInt m_width;
		UInt m_height;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new WindowResizeEvent.
		/// </summary>
		/// <param name="width">The new width.</param>
		/// <param name="height">The new height.</param>
		WindowResizeEvent(UInt width, UInt height)
			: m_width(width), m_height(height)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the new width of the Window.
		/// </summary>
		/// <returns>The new width.</returns>
		UInt get_width() const { return m_width; }

		/// <summary>
		/// Gets the new height of the Window.
		/// </summary>
		/// <returns>The new height.</returns>
		UInt get_height() const { return m_height; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the type of event for this class.
		/// </summary>
		/// <returns>The EventType.</returns>
		static EventType get_event_type() { return EventType::WindowResize; }

#pragma endregion
	};
}