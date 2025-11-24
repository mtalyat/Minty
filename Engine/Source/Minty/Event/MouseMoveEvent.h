#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Event/Event.h"

namespace Minty
{
	/// <summary>
	/// A MouseMoveEvent is triggered when the mouse is moved.
	/// </summary>
	class MouseMoveEvent
		: public Event
	{
#pragma region Variables

	private:
		Float2 m_position;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MouseMoveEvent.
		/// </summary>
		/// <param name="position">The position of the mouse.</param>
		MouseMoveEvent(Float2 const position)
			: m_position(position)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the position of this Event.
		/// </summary>
		/// <returns>The position.</returns>
		Float2 get_position() const { return m_position; }

		/// <summary>
		/// Gets the type of this Event.
		/// </summary>
		/// <returns>MouseMove.</returns>
		constexpr EventType get_type() const override { return EventType::MouseMove; }

#pragma endregion


	};
}