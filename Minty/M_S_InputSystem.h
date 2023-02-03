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
	private:
	public:
		InputSystem(entt::registry* const registry)
			: System(registry)
		{}

		void update() override;

		void onMouseDown(Click const* const click);

		void onMouseUp(Click const* const click);
	};
}