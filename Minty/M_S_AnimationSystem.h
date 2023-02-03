#pragma once

#include "M_System.h"

namespace minty
{
	/// <summary>
	/// Handles all animations within the Scene.
	/// </summary>
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