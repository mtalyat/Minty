#pragma once

#include "M_System.h"
#include "M_Rect.h"
#include "M_RectF.h"
#include "entt.hpp"

#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_Velocity.h"
#include "M_C_Collider.h"
#include "M_Collision.h"

namespace minty
{
	class MINTY_API CollisionSystem
		: public System
	{
	private:
		int m_cellSize;

		std::map<Point, std::vector<entt::entity>*>* mp_cells;
		std::map<entt::entity, std::set<entt::entity>>* mp_relationships;

	public:
		CollisionSystem(entt::registry* const registry, int const cellSize)
			: System(registry)
			, m_cellSize(cellSize)
			, mp_cells(new std::map<Point, std::vector<entt::entity>*>())
			, mp_relationships(new std::map<entt::entity, std::set<entt::entity>>())
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

		void emplaceOnEnter(entt::entity const entity, Event<Collision* const>::func const& func);
		void emplaceOnStay(entt::entity const entity, Event<Collision* const>::func const& func);
		void emplaceOnExit(entt::entity const entity, Event<Collision* const>::func const& func);

	private:
		void updateEntity(entt::entity const entity);

		void addToCell(Point const& pos, entt::entity const entity);

		void addToCells(Rect const& cellBounds, entt::entity const entity);

		void removeFromCell(Point const& pos, entt::entity const entity);

		void removeFromCells(Rect const& cellBounds, entt::entity const entity);

		void onCollision(entt::entity const entity, entt::entity const other);

		void shiftOutOfCollision(entt::entity const entity, Position& pos, Velocity& vel, Collider const& collider, entt::entity const other, RectF const& otherWorldHitbox, Collider const& otherCollider);

		Rect getCellBounds(RectF const& worldHitbox) const;

		RectF getWorldHitbox(Position const& pos, Collider const& collider) const;
	};
}