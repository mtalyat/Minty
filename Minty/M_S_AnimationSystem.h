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
		/// <summary>
		/// Creates a new AnimationSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		AnimationSystem(entt::registry* const registry)
			: System(registry)
		{}

		void update() override;
	};
}