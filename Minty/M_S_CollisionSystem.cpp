#include "pch.h"
#include "M_S_CollisionSystem.h"

#include "M_C_Name.h"
#include "M_C_Renderer.h"

#include "M_Debug.h"

#include "M_Line.h"
#include "M_RectF.h"
#include "M_Mask.h"

namespace minty
{
	void CollisionSystem::update()
	{
		mp_registry->view<Collider, Position>().each([this](auto entity, auto& collider, auto const& pos)
			{
				// assume entity has moved
// check if cell bounds are the same

				RectF worldHitbox = getWorldHitbox(pos, collider);

		Rect bounds = getCellBounds(worldHitbox);

		if (collider.cellBounds != bounds)
		{
			// moved

			// remove from old lists
			removeFromCells(collider.cellBounds, entity);

			// add to new ones
			addToCells(bounds, entity);

			// update bounds
			collider.cellBounds = bounds;
		}
			});

		// check for collisions
		// for now, just debug if there is one

		std::set<entt::entity> oldEntities;

		std::unordered_map<entt::entity, entt::entity> notColliding;

		// go through each cell
		for (auto pair : *mp_cells)
		{
			// if more than one object within the cell, check for collisions
			if (pair.second->size() > 1)
			{
				int size = static_cast<int>(pair.second->size());

				for (int i = 0; i < size - 1; i++)
				{
					entt::entity e1 = pair.second->at(i);

					if (!mp_registry->valid(e1))
					{
						oldEntities.emplace(e1);
						continue;
					}

					Position& position1 = mp_registry->get<Position>(e1);
					Collider const hitbox1 = mp_registry->get<Collider>(e1);
					RectF worldHitbox1 = getWorldHitbox(position1, hitbox1);
					Renderer const* renderer1 = mp_registry->try_get<Renderer>(e1);

					for (int j = i + 1; j < size; j++)
					{
						entt::entity e2 = pair.second->at(j);

						if (!mp_registry->valid(e2))
						{
							oldEntities.emplace(e2);
							continue;
						}

						Position& position2 = mp_registry->get<Position>(e2);
						Collider const hitbox2 = mp_registry->get<Collider>(e2);
						RectF worldHitbox2 = getWorldHitbox(position2, hitbox2);
						Renderer const* renderer2 = mp_registry->try_get<Renderer>(e2);

						// find world overlap
						RectF worldOverlap = worldHitbox1.overlap(worldHitbox2);
						worldOverlap.x += worldHitbox1.x;
						worldOverlap.y += worldHitbox1.y;

						Collision collision1 = { e1, &hitbox1, e2, &hitbox2, worldOverlap };
						Collision collision2 = { e2, &hitbox2, e1, &hitbox1, worldOverlap };

						// check for overlap
						if (!worldHitbox1.overlaps(worldHitbox2))
						{
							// no overlap
							if (isColliding(e1, e2))
							{
								onCollisionEnd(collision1);
								onCollisionEnd(collision2);
							}
							continue;
						}

						// get overlap, check pixels
						if (renderer1 && renderer2)
						{
							Rect overlap1 = Rect::round(worldHitbox1.overlap(worldHitbox2));
							Rect overlap2 = Rect::round(worldHitbox2.overlap(worldHitbox1));

							// ensure there are masks
							renderer1->sprite->generateMask();
							renderer2->sprite->generateMask();

							Mask slice1 = renderer1->sprite->getMask()->slice(overlap1);
							Mask slice2 = renderer2->sprite->getMask()->slice(overlap2);

							if (!slice1.sameSize(slice2))
							{
								continue;
							}

							if (!slice1.collidesWith(slice2))
							{
								// no collision
								if (isColliding(e1, e2))
								{
									onCollisionEnd(collision1);
									onCollisionEnd(collision2);
								}
								continue;
							}

							// collisions, not triggers
							if (!hitbox1.isTrigger && !hitbox2.isTrigger)
							{
								Velocity* vel1 = mp_registry->try_get<Velocity>(e1);
								Velocity* vel2 = mp_registry->try_get<Velocity>(e2);

								// if no velocity, treat as solid
								// if velocity, push both
								if (vel1 && vel2)
								{
									// both have velocity
									//Debug::logNotImplemented("Two moving objects collision handling", "CollisionSystem::update()", "M_S_CollisionSystem.cpp");
								}
								else if (vel1 && !vel2)
								{
									// 1 has velocity

									shiftOutOfCollision(collision1, position1, *vel1, renderer1, worldHitbox1, worldHitbox2, renderer2, worldOverlap);
								}
								else if (!vel1 && vel2)
								{
									// 2 has velocity

									shiftOutOfCollision(collision2, position2, *vel2, renderer2, worldHitbox2, worldHitbox1, renderer1, worldOverlap);
								}
								else
								{
									// neither have velocity
									//Debug::logNotImplemented("Two non-moving objects collision handling", "CollisionSystem::update()", "M_S_CollisionSystem.cpp");
								}
							}
						}

						// collision detected, trigger events

						// pass in appropriate collision data for each side
						onCollision(collision1);
						onCollision(collision2);
					}
				}

				// remove old entities that no longer exist
				if (oldEntities.size())
				{
					for (int i = pair.second->size() - 1; i >= 0; i--)
					{
						if (oldEntities.contains(pair.second->at(i)))
						{
							pair.second->erase(pair.second->begin() + i);
						}
					}
					oldEntities.clear();
				}
			}
		}
	}

	void CollisionSystem::emplaceOnEnter(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnEnter(func);
	}

	void CollisionSystem::emplaceOnStay(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnStay(func);
	}

	void CollisionSystem::emplaceOnExit(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnExit(func);
	}

	bool CollisionSystem::isColliding(entt::entity const e1, entt::entity const e2)
	{
		auto found = mp_relationships->find(e1);

		if (found != mp_relationships->end())
		{
			if (found->second.contains(e2))
			{
				return true;
			}
		}

		return false;
	}

	void CollisionSystem::addToCell(Point const& pos, entt::entity const entity)
	{
		auto found = mp_cells->find(pos);

		if (found == mp_cells->end())
		{
			// new cell
			mp_cells->emplace(pos, new std::vector<entt::entity>());
		}

		// put into set
		mp_cells->at(pos)->push_back(entity);
	}

	void CollisionSystem::addToCells(Rect const& cellBounds, entt::entity const entity)
	{
		Point cellPos;

		for (int y = 0; y < cellBounds.height; y++)
		{
			for (int x = 0; x < cellBounds.width; x++)
			{
				cellPos = Point(x + cellBounds.x, y + cellBounds.y);
				addToCell(cellPos, entity);
			}
		}
	}

	void CollisionSystem::removeFromCell(Point const& pos, entt::entity const entity)
	{
		auto found = mp_cells->find(pos);

		if (found != mp_cells->end())
		{
			// found the list
			// remove entity
			for (size_t i = 0; i < found->second->size(); i++)
			{
				if (found->second->at(i) == entity)
				{
					found->second->erase(found->second->begin() + i);
					break;
				}
			}

			// if empty, delete it entirely
			if (found->second->empty())
			{
				std::vector<entt::entity>* emptyList = found->second;
				mp_cells->erase(pos);
				delete emptyList;
			}
		}
	}

	void CollisionSystem::removeFromCells(Rect const& cellBounds, entt::entity const entity)
	{
		Point cellPos;

		for (int y = 0; y < cellBounds.height; y++)
		{
			for (int x = 0; x < cellBounds.width; x++)
			{
				cellPos = Point(x + cellBounds.x, y + cellBounds.y);
				removeFromCell(cellPos, entity);
			}
		}
	}

	void CollisionSystem::onCollision(Collision const& collision)
	{
		if (!mp_relationships->contains(collision.entity))
		{
			mp_relationships->emplace(collision.entity, std::set<entt::entity>());
			mp_relationships->at(collision.entity).emplace(collision.otherEntity);

			collision.collider->triggerOnEnter(collision);
		}
		else if (!mp_relationships->at(collision.entity).contains(collision.otherEntity))
		{
			mp_relationships->at(collision.entity).emplace(collision.otherEntity);

			collision.collider->triggerOnEnter(collision);
		}

		collision.collider->triggerOnStay(collision);
	}

	void CollisionSystem::onCollisionEnd(Collision const& collision)
	{
		// find relationship
		auto found = mp_relationships->find(collision.entity);

		if (found != mp_relationships->end())
		{
			// ok, find actual relationship
			if (found->second.contains(collision.otherEntity))
			{
				// relationship found
				// remove
				found->second.erase(collision.otherEntity);

				// if list is empty, remove key
				if (found->second.size() == 0)
				{
					mp_relationships->erase(collision.entity);
				}

				// call event
				if (collision.collider->onExit)
				{
					collision.collider->onExit->invoke(collision);
				}
			}
		}
	}

	void CollisionSystem::shiftOutOfCollision(Collision const& collision, Position& position, Velocity& velocity, Renderer const* const renderer, RectF const& worldHitbox, RectF const& otherWorldHitbox, Renderer const* const otherRenderer, RectF const& worldOverlap)
	{
		// move 1 backwards until not colliding
		// move towards center of entity
		//PointF direction = worldHitbox.center() - otherWorldHitbox.center();
		//PointF direction = worldHitbox.center() - worldOverlap.center();
		PointF direction(-velocity.x, -velocity.y);

		float incX, incY;
		line_normalized(0, 0, math_roundToInt(direction.x), math_roundToInt(direction.y), incX, incY);

		// no longer moving
		velocity.x = 0.0f;
		velocity.y = 0.0f;

		float x = position.x;
		float y = position.y;

		// max distance
		int max = collision.collider->bounds.area();

		for (int i = 0; i < max; i++)
		{
			// move pos
			position.x += incX;
			position.y += incY;

			// check new pos
			RectF worldHitbox = this->getWorldHitbox(position, *collision.collider);

			if (renderer && otherRenderer)
			{
				// get overlaps
				Rect overlap1 = Rect::round(worldHitbox.overlap(otherWorldHitbox));
				Rect overlap2 = Rect::round(otherWorldHitbox.overlap(worldHitbox));

				// check pixels
				Mask slice1 = renderer->sprite->getMask()->slice(overlap1);
				Mask slice2 = otherRenderer->sprite->getMask()->slice(overlap2);

				if (!slice1.collidesWith(slice2))
				{
					// no collision
					// done searching
					break;
				}
			}
			else
			{
				if (!worldHitbox.overlaps(otherWorldHitbox))
				{
					// no overlap
					// does not even overlap anymore
					break;
				}
			}
		}
	}

	Rect CollisionSystem::getCellBounds(RectF const& worldHitbox) const
	{
		return Rect::bounds(
			math_floorToInt(worldHitbox.left() / m_cellSize),
			math_floorToInt(worldHitbox.right() / m_cellSize),
			math_floorToInt(worldHitbox.top() / m_cellSize),
			math_floorToInt(worldHitbox.bottom() / m_cellSize));
	}

	RectF CollisionSystem::getWorldHitbox(Position const& pos, Collider const& hitbox) const
	{
		Rect hitboxRect = hitbox.bounds;

		return RectF(pos.x + hitboxRect.x, pos.y + hitboxRect.y, static_cast<float>(hitboxRect.width), static_cast<float>(hitboxRect.height));
	}
}