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

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>WindowClose.</returns>
		constexpr EventType get_type() const override { return EventType::WindowClose; }

#pragma endregion
	};
}