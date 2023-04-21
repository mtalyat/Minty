#pragma once

#include "M_System.h"

#include "M_Click.h"

namespace minty
{
	/// <summary>
	/// Handles all inputs within the Scene, excluding those within the Input class.
	/// </summary>
	class MINTY_API InputSystem
		: public System
	{
	public:
		/// <summary>
		/// Creates a new InputSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		InputSystem(entt::registry* const registry)
			: System(registry)
		{}

		void update() override;

		/// <summary>
		/// Called when the mouse is pressed down.
		/// </summary>
		/// <param name="click"></param>
		void onMouseDown(Click const* const click);

		/// <summary>
		/// Called when the mouse is released.
		/// </summary>
		/// <param name="click"></param>
		void onMouseUp(Click const* const click);
	};
}