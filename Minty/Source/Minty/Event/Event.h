#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Event/EventType.h"
#include <functional>

namespace Minty
{
	/// <summary>
	/// Holds data about an Event.
	/// </summary>
	class Event
	{
#pragma region Variables

	private:
		Bool m_handled;

#pragma endregion

#pragma region Constructors

	public:
		virtual ~Event() = default;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this Event has been handled.
		/// </summary>
		/// <returns>True, if this Event has been handled.</returns>
		Bool is_handled() const { return m_handled; }

		/// <summary>
		/// Marks this Event as handled.
		/// </summary>
		void mark_as_handled() { m_handled = true; }

#pragma endregion
	};

	using EventCallbackFunction = std::function<void(Event const&)>;
}