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
#include "M_Collision.h"

namespace minty
{
	/// <summary>
	/// Handles all collisions within the Scene.
	/// </summary>
	class MINTY_API CollisionSystem
		: public System
	{
	private:
		int m_cellSize;

		std::unordered_map<Point, std::vector<entt::entity>*>* mp_cells;
		std::unordered_map<entt::entity, std::set<entt::entity>>* mp_relationships;

	public:
		CollisionSystem(entt::registry* const registry, int const cellSize)
			: System(registry)
			, m_cellSize(cellSize)
			, mp_cells(new std::unordered_map<Point, std::vector<entt::entity>*>())
			, mp_relationships(new std::unordered_map<entt::entity, std::set<entt::entity>>())
		{}

		~CollisionSystem() override
		{
			for (auto pair : *mp_cells)
			{
				delete pair.second;
			}

			delete mp_cells;

			delete mp_relationships;
		}

		void update() override;

		void emplaceOnEnter(entt::entity const entity, collider_event_t::func const& func);
		void emplaceOnStay(entt::entity const entity, collider_event_t::func const& func);
		void emplaceOnExit(entt::entity const entity, collider_event_t::func const& func);

	private:
		bool isColliding(entt::entity const e1, entt::entity const e2);

		void addToCell(Point const& pos, entt::entity const entity);

		void addToCells(Rect const& cellBounds, entt::entity const entity);

		void removeFromCell(Point const& pos, entt::entity const entity);

		void removeFromCells(Rect const& cellBounds, entt::entity const entity);

		void onCollision(Collision const& collision);

		void onCollisionEnd(Collision const& collision);

		void shiftOutOfCollision(Collision const& collision, Position& pos, Velocity& vel, RectF const& worldHitbox, RectF const& otherWorldHitbox, RectF const& worldOverlap);

		Rect getCellBounds(RectF const& worldHitbox) const;

		RectF getWorldHitbox(Position const& pos, Collider const& collider) const;
	};
}