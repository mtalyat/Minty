#pragma once

#include "M_System.h"

#include "M_MouseClickEvent.h"

namespace minty
{
	/// <summary>
	/// Handles all inputs within the Scene, excluding those within the Input class.
	/// </summary>
	class MINTY_API InputSystem
		: public System
	{
	private:
		int m_mouseX, m_mouseY;

	public:
		/// <summary>
		/// Creates a new InputSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		InputSystem(entt::registry* const registry)
			: System(registry)
			, m_mouseX(-1)
			, m_mouseY(-1)
		{}

		/// <summary>
		/// Called when the mouse is pressed down.
		/// </summary>
		/// <param name="click">The click event data.</param>
		bool onMouseDown(MouseClickEvent const* const click);

		/// <summary>
		/// Called when the mouse is released.
		/// </summary>
		/// <param name="click">The click event data.</param>
		bool onMouseUp(MouseClickEvent const* const click);

		/// <summary>
		/// Called when the mouse is moved.
		/// </summary>
		/// <param name="x">The new X position of the mouse.</param>
		/// <param name="y">The new Y position of the mouse.</param>
		void onMouseMove(int const x, int const y);
	};
}