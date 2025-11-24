#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// A MouseScrollEvent is triggered when the mouse is scrolled.
	/// </summary>
	class MouseScrollEvent
		: public Event
	{
#pragma region Variables

	private:
		Float2 m_offset;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MouseScrollEvent.
		/// </summary>
		/// <param name="offset">The offset of the mouse.</param>
		MouseScrollEvent(Float2 const offset)
			: m_offset(offset)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the offset of this Event.
		/// </summary>
		/// <returns>The offset.</returns>
		Float2 get_offset() const { return m_offset; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>MouseScroll.</returns>
		constexpr EventType get_type() const override { return EventType::MouseScroll; }

#pragma endregion
	};
}