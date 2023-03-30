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
		int m_cellSize;

		std::unordered_map<Point, std::vector<entt::entity>*>* mp_cells;
		std::unordered_map<entt::entity, std::set<entt::entity>>* mp_relationships;

	public:
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

		void emplaceOnEnter(entt::entity const entity, collider_event_t::func const& func);
		void emplaceOnStay(entt::entity const entity, collider_event_t::func const& func);
		void emplaceOnExit(entt::entity const entity, collider_event_t::func const& func);

	private:
		bool checkCollision(entt::entity const entity, Collider const& collider, Mask* const mask, RectF const& worldHitbox, PointF const& offset);

		bool isInRelationship(entt::entity const e1, entt::entity const e2);

		void addToCell(Point const& pos, entt::entity const entity);

		void addToCells(Rect const& cellBounds, entt::entity const entity);

		void removeFromCell(Point const& pos, entt::entity const entity);

		void removeFromCells(Rect const& cellBounds, entt::entity const entity);

		void triggerCollisionEnterEvent(Collision const& collision);

		void triggerCollisionEndEvent(Collision const& collision);

		Mask* getMask(entt::entity const entity, Collider const& collider) const;

		PointF getOffset(entt::entity const entity) const;

		Rect getCellBounds(RectF const& worldHitbox) const;

		RectF getWorldHitbox(Position const& pos, Collider const& collider) const;

		void updateCellBounds(Collider& collider, RectF const& worldHitbox, entt::entity const entity);
	};
}