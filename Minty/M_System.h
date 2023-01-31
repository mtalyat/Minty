#pragma once

#include "M_Object.h"
#include "entt.hpp"

namespace minty
{
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

		virtual ~System() {}

		/// <summary>
		/// Adds an entity to the System.
		/// </summary>
		/// <param name="entity"></param>
		virtual bool emplace(entt::entity const entity) = 0;

		/// <summary>
		/// Removes an entity from the System.
		/// </summary>
		/// <param name="entity"></param>
		virtual bool erase(entt::entity const entity) = 0;

		/// <summary>
		/// Does one frame of work on the System.
		/// </summary>
		virtual void update() = 0;
	};
}