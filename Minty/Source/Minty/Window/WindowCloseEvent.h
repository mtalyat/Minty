#pragma once
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// Holds data about a WindowCloseEvent.
	/// </summary>
	class WindowCloseEvent
		: public Event
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new WindowCloseEvent.
		/// </summary>
		WindowCloseEvent()
		{
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the type of event for this class.
		/// </summary>
		/// <returns>The EventType.</returns>
		static EventType get_event_type() { return EventType::WindowClose; }

#pragma endregion
	};
}