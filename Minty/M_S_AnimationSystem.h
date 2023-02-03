#pragma once

#include "M_System.h"

namespace minty
{
	class MINTY_API AnimationSystem
		: public System
	{
	public:
		AnimationSystem(entt::registry* const registry)
			: System(registry)
		{}

		void update() override;
	};
}