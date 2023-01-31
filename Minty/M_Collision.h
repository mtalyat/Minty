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
		entt::entity entity;

		Collider* collider;

		entt::entity otherEntity;

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