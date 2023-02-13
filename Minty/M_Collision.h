#pragma once

#include "M_Main.h"
#include "M_RectF.h"
#include "entt.hpp"

namespace minty
{
	struct Collider;

	/// <summary>
	/// Holds data relevant to a collision between two entities.
	/// </summary>
	struct MINTY_API Collision
	{
		/// <summary>
		/// The entity that triggered this collision.
		/// </summary>
		entt::entity entity;

		/// <summary>
		/// The collider that belongs to this entity.
		/// </summary>
		Collider const* collider;

		/// <summary>
		/// The other entity that triggered this collision.
		/// </summary>
		entt::entity otherEntity;

		/// <summary>
		/// The other collider that belongs to the other entity.
		/// </summary>
		Collider const* otherCollider;

		/// <summary>
		/// The overlap between the two entities when they collided.
		/// </summary>
		RectF overlap;
	};
}