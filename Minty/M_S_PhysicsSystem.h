#pragma once

#include "M_System.h"

namespace minty
{
	constexpr float GRAVITY = 9.81f;

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