#pragma once

#include "M_System.h"

namespace minty
{
	/// <summary>
	/// Handles all movement and physics within the Scene, excluding collisions.
	/// </summary>
	class MINTY_API PhysicsSystem
		: public System
	{
	public:
		PhysicsSystem(entt::registry* const registry)
			: System(registry)
		{}

		~PhysicsSystem() override
		{}

		void update() override;
	};
}