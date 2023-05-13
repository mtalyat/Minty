#pragma once

#include "M_System.h"

#include "M_Rect.h"
#include "M_RectF.h"
#include "entt.hpp"

#include <unordered_map>

#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_Velocity.h"
#include "M_C_Collider.h"
#include "M_Mask.h"
#include "M_Collision.h"

namespace minty
{
	/// <summary>
	/// Handles all movement and physics within the Scene, excluding collisions.
	/// </summary>
	class MINTY_API PhysicsSystem
		: public System
	{
	private:
		// the size of each collision cell
		int m_cellSize;

		// the cells with collidable objects
		std::unordered_map<Point, std::vector<entt::entity>*>* mp_cells;
		// the collision relationships between entities
		std::unordered_map<entt::entity, std::set<entt::entity>>* mp_relationships;

	public:
		/// <summary>
		/// Creates a new PhysicsSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		/// <param name="cellSize">The size of each collision cell.</param>
		PhysicsSystem(entt::registry* const registry, int const cellSize)
			: System(registry)
			, m_cellSize(cellSize)
			, mp_cells(new std::unordered_map<Point, std::vector<entt::entity>*>())
			, mp_relationships(new std::unordered_map<entt::entity, std::set<entt::entity>>())
		{}

		~PhysicsSystem() override
		{
			for (auto pair : *mp_cells)
			{
				delete pair.second;
			}

			delete mp_cells;

			delete mp_relationships;
		}

		void fixedUpdate() override;

		/// <summary>
		/// Adds an onEnter event to the given entity.
		/// </summary>
		/// <param name="entity">The entity to add the function Event to.</param>
		/// <param name="func">The function to add to the Event.</param>
		void emplaceOnEnter(entt::entity const entity, collider_event_t::func const& func);
		/// <summary>
		/// Adds an onStay event to the given entity.
		/// </summary>
		/// <param name="entity">The entity to add the function Event to.</param>
		/// <param name="func">The function to add to the Event.</param>
		void emplaceOnStay(entt::entity const entity, collider_event_t::func const& func);
		/// <summary>
		/// Adds an onExit event to the given entity.
		/// </summary>
		/// <param name="entity">The entity to add the function Event to.</param>
		/// <param name="func">The function to add to the Event.</param>
		void emplaceOnExit(entt::entity const entity, collider_event_t::func const& func);

	private:
		// check a collision for this entity
		bool checkCollision(entt::entity const entity, Collider const& collider, Mask* const mask, RectF const& worldHitbox, PointF const& offset);

		// checks if the two entites have been colliding
		bool isInRelationship(entt::entity const e1, entt::entity const e2);

		// adds an entity to a cell at the given position
		void addToCell(Point const& pos, entt::entity const entity);

		// adds the entity to all cells within the cell bounds
		void addToCells(Rect const& cellBounds, entt::entity const entity);

		// removes the entity from the cell at the given position
		void removeFromCell(Point const& pos, entt::entity const entity);

		// removes the entity from all cells within the cell bounds
		void removeFromCells(Rect const& cellBounds, entt::entity const entity);

		// trigger onEnter event for the collision
		void triggerCollisionEnterEvent(Collision const& collision);

		// trigger onStay event for the collision
		void triggerCollisionStayEvent(Collision const& collision);

		// trigger onExit event for the collision
		void triggerCollisionEndEvent(Collision const& collision);

		// get the mask of the entity
		Mask* getMask(entt::entity const entity, Collider const& collider) const;

		// get the render offset of the entity
		PointF getOffset(entt::entity const entity) const;

		// the cell bounds of the entity
		Rect getCellBounds(RectF const& worldHitbox) const;

		// the world hitbox of the given position and collider
		RectF getWorldHitbox(Position const& pos, Collider const& collider) const;

		// update the cell bounds for the given entity
		void updateCellBounds(Collider& collider, RectF const& worldHitbox, entt::entity const entity);
	};
}