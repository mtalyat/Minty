#pragma once

#include "M_Object.h"
#include "entt.hpp"

namespace minty
{
	struct Collider;

	/// <summary>
	/// Holds data relevant to a collision between two entities.
	/// </summary>
	struct MINTY_API Collision
		: public Object
	{
		/// <summary>
		/// The entity that triggered this collision.
		/// </summary>
		entt::entity entity;

		/// <summary>
		/// The collider that belongs to this entity.
		/// </summary>
		Collider* collider;

		/// <summary>
		/// The other entity that triggered this collision.
		/// </summary>
		entt::entity otherEntity;

		/// <summary>
		/// The other collider that belongs to the other entity.
		/// </summary>
		Collider* otherCollider;

		Collision(entt::entity const ent, Collider* const col, entt::entity const otherEnt, Collider* otherCol)
			: Object()
			, entity(ent)
			, collider(col)
			, otherEntity(otherEnt)
			, otherCollider(otherCol)
		{}
	};
}