#pragma once

#include "M_System.h"

namespace minty
{
	/// <summary>
	/// Handles all following, and targeting for entities.
	/// </summary>
	class MINTY_API TargetSystem
		: public System
	{
	public:
		/// <summary>
		/// Creates a new TargetSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		TargetSystem(entt::registry* const registry)
			: System(registry)
		{}

		virtual void fixedUpdate() override;
	};
}