#pragma once

#include "M_Object.h"
#include "entt.hpp"
#include <set>

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

		/// <summary>
		/// The entities within this System.
		/// </summary>
		std::set<entt::entity>* mp_entities;

	public:
		System(entt::registry* const registry)
			: mp_registry(registry)
			, mp_entities(new std::set<entt::entity>())
		{}

		virtual ~System()
		{
			delete mp_entities;
		}

		/// <summary>
		/// Adds an entity to the System.
		/// </summary>
		/// <param name="entity"></param>
		virtual bool emplace(entt::entity const entity);

		/// <summary>
		/// Removes an entity from the System.
		/// </summary>
		/// <param name="entity"></param>
		virtual bool erase(entt::entity const entity);

		/// <summary>
		/// Does one frame of work on the System.
		/// </summary>
		virtual void update() = 0;
	};
}