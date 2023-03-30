#pragma once

#include "M_Object.h"
#include "entt.hpp"
#include <set>

namespace minty
{
	/// <summary>
	/// The base class for systems, which provide functionality and conduct the behavior of the ECS engine.
	/// </summary>
	class MINTY_API System
		: public Object
	{
	protected:
		/// <summary>
		/// The registry that this System is part of.
		/// </summary>
		entt::registry* const mp_registry;

	public:
		System(entt::registry* const registry)
			: mp_registry(registry)
		{}

		virtual ~System(){}

		/// <summary>
		/// Called when the Scene is being loaded.
		/// </summary>
		virtual void load() {}

		/// <summary>
		/// Does one frame of work on the System.
		/// </summary>
		virtual void update() {}

		/// <summary>
		/// Does one fixed frame of work on the System.
		/// </summary>
		virtual void fixedUpdate() {}

		/// <summary>
		/// Called when the Scene is being unloaded.
		/// </summary>
		virtual void unload() {}
	};
}