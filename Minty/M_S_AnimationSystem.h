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

		bool emplace(entt::entity const entity) override;

		void update() override;
	};
}