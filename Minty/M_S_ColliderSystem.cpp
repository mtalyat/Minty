#include "pch.h"
#include "M_S_CollisionSystem.h"

#include "M_Debug.h"

#include "M_Line.h"
#include "M_RectF.h"
#include "M_Mask.h"

namespace minty
{
	void CollisionSystem::updateEntity(entt::entity const entity)
	{
		// assume entity has moved
		// check if cell bounds are the same
		Position const& pos = mp_registry->get<Position>(entity);
		Collider& hitbox = mp_registry->get<Collider>(entity);

		RectF worldHitbox = getWorldHitbox(pos, hitbox);

		Rect bounds = getCellBounds(worldHitbox);

		if (hitbox.cellBounds != bounds)
		{
			// moved

			// remove from old lists
			removeFromCells(hitbox.cellBounds, entity);

			// add to new ones
			addToCells(bounds, entity);

			// update bounds
			hitbox.cellBounds = bounds;
		}
	}

	void CollisionSystem::update()
	{
		mp_registry->view<Collider>().each([this](auto entity, auto& collider)
			{
				updateEntity(entity);
			});

		// check for collisions
		// for now, just debug if there is one

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
					Position& position1 = mp_registry->get<Position>(e1);
					Collider const hitbox1 = mp_registry->get<Collider>(e1);
					RectF worldHitbox1 = getWorldHitbox(position1, hitbox1);

					for (int j = i + 1; j < size; j++)
					{
						entt::entity e2 = pair.second->at(j);
						Position& position2 = mp_registry->get<Position>(e2);
						Collider const hitbox2 = mp_registry->get<Collider>(e2);
						RectF worldHitbox2 = getWorldHitbox(position2, hitbox2);

						// check for overlap
						if (!worldHitbox1.overlaps(worldHitbox2))
						{
							// no overlap
							continue;
						}

						// get overlap, check pixels
						if (hitbox1.hitbox->mask() && hitbox2.hitbox->mask())
						{
							Rect overlap1 = Rect::round(worldHitbox1.overlap(worldHitbox2));
							Rect overlap2 = Rect::round(worldHitbox2.overlap(worldHitbox1));

							Mask slice1 = hitbox1.hitbox->mask()->slice(overlap1);
							Mask slice2 = hitbox2.hitbox->mask()->slice(overlap2);

							if (!slice1.sameSize(slice2))
							{
								continue;
							}

							if (!slice1.collidesWith(slice2))
							{
								// no collision
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
									Debug::logNotImplemented("Two moving objects collision handling", "CollisionSystem::update()", "M_S_CollisionSystem.cpp");
								}
								else if (vel1 && !vel2)
								{
									// 1 has velocity

									shiftOutOfCollision(e1, position1, *vel1, hitbox1, e2, worldHitbox2, hitbox2);
								}
								else if (!vel1 && vel2)
								{
									// 2 has velocity

									shiftOutOfCollision(e2, position2, *vel2, hitbox2, e1, worldHitbox1, hitbox1);
								}
								else
								{
									// neither have velocity
									Debug::logNotImplemented("Two non-moving objects collision handling", "CollisionSystem::update()", "M_S_CollisionSystem.cpp");
								}
							}
						}

						// collision detected

						// trigger events

						onCollision(e1, e2);
						onCollision(e2, e1);
					}
				}
			}
		}

		// TODO: trigger on exit
	}

	void CollisionSystem::emplaceOnEnter(entt::entity const entity, Event<Collision* const>::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		if (!collider->onEnter)
		{
			// no event
			collider->onEnter = new Event<Collision* const>();
		}

		collider->onEnter->emplace(func);
	}

	void CollisionSystem::emplaceOnStay(entt::entity const entity, Event<Collision* const>::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		if (!collider->onStay)
		{
			// no event
			collider->onStay = new Event<Collision* const>();
		}

		collider->onStay->emplace(func);
	}

	void CollisionSystem::emplaceOnExit(entt::entity const entity, Event<Collision* const>::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		if (!collider->onExit)
		{
			// no event
			collider->onExit = new Event<Collision* const>();
		}

		collider->onExit->emplace(func);
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

	void CollisionSystem::onCollision(entt::entity const entity, entt::entity const other)
	{
		Collider* collider = &mp_registry->get<Collider>(entity);

		Collision collision(entity, collider, other, &mp_registry->get<Collider>(other));

		if (!mp_relationships->contains(entity))
		{
			mp_relationships->emplace(entity, std::set<entt::entity>());
			mp_relationships->at(entity).emplace(other);

			collider->triggerOnEnter(&collision);
		}
		else if (!mp_relationships->at(entity).contains(other))
		{
			mp_relationships->at(entity).emplace(other);

			collider->triggerOnEnter(&collision);
		}

		collider->triggerOnStay(&collision);
	}

	void CollisionSystem::shiftOutOfCollision(entt::entity const entity, Position& position, Velocity& velocity, Collider const& hitbox, entt::entity const other, RectF const& otherWorldHitbox, Collider const& otherHitbox)
	{
		// move 1 backwards until not colliding
		float incX, incY;
		line_normalized(math_floorToInt(position.x), math_floorToInt(position.y), math_floorToInt(position.x - velocity.x), math_floorToInt(position.y - velocity.y), incX, incY);

		// no longer moving
		velocity.x = 0.0f;
		velocity.y = 0.0f;

		float x = position.x;
		float y = position.y;

		// max distance
		int max = hitbox.hitbox->rect().area();

		for (int i = 0; i < max; i++)
		{
			// move pos
			position.x += incX;
			position.y += incY;

			// check new pos
			RectF worldHitbox = getWorldHitbox(position, hitbox);

			Rect overlap1 = Rect::round(worldHitbox.overlap(otherWorldHitbox));
			Rect overlap2 = Rect::round(otherWorldHitbox.overlap(worldHitbox));

			Mask slice1 = hitbox.hitbox->mask()->slice(overlap1);
			Mask slice2 = otherHitbox.hitbox->mask()->slice(overlap2);

			if (!slice1.collidesWith(slice2))
			{
				// no collision
				// done searching
				break;
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
		Rect hitboxRect = hitbox.hitbox->rect();

		return RectF(pos.x + hitboxRect.x, pos.y + hitboxRect.y, static_cast<float>(hitboxRect.width), static_cast<float>(hitboxRect.height));
	}
}