#include "pch.h"
#include "M_S_PhysicsSystem.h"

#include "M_Time.h"
#include "M_Line.h"

#include "M_C_Acceleration.h"
#include "M_C_Velocity.h"
#include "M_C_Position.h"
#include "M_C_Gravity.h"
#include "M_C_SpriteRenderer.h"

#include "M_Debug.h"
#include "M_C_Name.h"

namespace minty
{
	void PhysicsSystem::fixedUpdate()
	{
		// for each entity with velocity, collider
		//		get future position
		//		if entity in the way, check for collision
		//			if collision, step from start to new spot, stop one hit something, stop velocity
		//		if no collision, just move there

		float deltaTime = Time::fixedDeltaTime();

		float gravityDeltaTime = GRAVITY * deltaTime;

		// apply gravity
		for (auto [entity, velocity, gravity] : mp_registry->view<Velocity, Gravity const>().each())
		{
			velocity.y += gravityDeltaTime * gravity.scale;
		}

		// apply acceleration
		for (auto [entity, velocity, acceleration] : mp_registry->view<Velocity, Acceleration const>().each())
		{
			velocity.x += acceleration.x * deltaTime;
			velocity.y += acceleration.y * deltaTime;
		}

		// apply velocity, no collider
		for (auto [entity, position, velocity] : mp_registry->view<Position, Velocity const>(entt::exclude<Collider>).each())
		{
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;
		}

		// ensure all entities with collider are in bounds for collision checking
		for (auto [entity, position, collider] : mp_registry->view<Position const, Collider>().each())
		{
			updateCellBounds(collider, getWorldHitbox(position, collider), entity);
		}

		// apply velocity, with collider
		for (auto [entity, collider, position, velocity] : mp_registry->view<Collider, Position, Velocity>().each())
		{
			// get world bounds
			RectF worldHitbox = getWorldHitbox(position, collider);

			// get mask
			Mask* mask = getMask(entity, collider);

			float velx = velocity.x * deltaTime;
			float vely = velocity.y * deltaTime;

			float futurex = position.x + velx;
			float futurey = position.y + vely;

			// start moving, check for collisions each step
			float incx, incy;
			int steps = line_normalized(position.x, position.y, futurex, futurey, incx, incy) + 1;

			float movex = 0.0f;
			float movey = 0.0f;

			int i;

			for (i = 0; i < steps; i++)
			{
				// check next position
				movex += incx;
				movey += incy;

				// if can move there, keep going
				// if cannot, stop moving
				if (checkCollision(entity, collider, mask, RectF(worldHitbox.x + movex, worldHitbox.y + movey, worldHitbox.width, worldHitbox.height), getOffset(entity)))
				{
					// collision, so stop moving
					// if no steps have occured yet, zero out smaller inc and try again
					if (i == 0)
					{
						if (math_abs(incx) < math_abs(incy) && math_abs(incx) != 0.0f)
						{
							i--;
							movex = 0.0f;
							movey = 0.0f;
							incx = 0.0f;
							futurex = position.x;
							continue;
						}
						else if (math_abs(incy) < math_abs(incx) && math_abs(incy) != 0.0f)
						{
							i--;
							movex = 0.0f;
							movey = 0.0f;
							incy = 0.0f;
							futurey = position.y;
							continue;
						}
					}
					
					// return to previous position
					movex -= incx;
					movey -= incy;

					// stop moving, based on increment
					velocity.x *= velx == 0.0f ? 0.0f : movex / velx;
					velocity.y *= vely == 0.0f ? 0.0f : movey / vely;

					break;
				}

				// no collision, move on to next iteration
			}

			// done moving, either is going to hit something next step, or made it all the way

			// set to new position
			if (i == steps)
			{
				// did not collide
				position.x = futurex;
				position.y = futurey;
			}
			else
			{
				// did collide
				position.x += movex;
				position.y += movey;
			}

			// if moved, update grids
			if (movex != 0.0f || movey != 0.0f)
			{
				updateCellBounds(collider, worldHitbox, entity);
			}
		}

		// trigger all on stays, as they should be all that is left within the relationships
		for (auto& pair : *mp_relationships)
		{
			// get collider for this entity
			Collider* collider = mp_registry->try_get<Collider>(pair.first);

			if (!collider)
			{
				continue;
			}

			// trigger for each relationship
			for (auto const other : pair.second)
			{
				// TODO: get overlap box for triggerStay
				collider->triggerOnStay({ pair.first, collider, other, mp_registry->try_get<Collider>(other), RectF() });
			}
		}
	}

	void PhysicsSystem::emplaceOnEnter(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnEnter(func);
	}

	void PhysicsSystem::emplaceOnStay(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnStay(func);
	}

	void PhysicsSystem::emplaceOnExit(entt::entity const entity, collider_event_t::func const& func)
	{
		Collider* collider = mp_registry->try_get<Collider>(entity);

		if (!collider)
		{
			// no collider to add the func to
			return;
		}

		collider->emplaceOnExit(func);
	}

	bool PhysicsSystem::checkCollision(entt::entity const entity, Collider const& collider, Mask* const mask, RectF const& worldHitbox, PointF const& offset)
	{
		// check overlap against all entities in the applicable cells
		Rect bounds = getCellBounds(worldHitbox);

		std::set<entt::entity> oldEntities;
		std::vector<entt::entity>* cell;

		bool collisionDetected = false;

		for (int y = 0; y < bounds.height; y++)
		{
			for (int x = 0; x < bounds.width; x++)
			{
				// if cell has entities, grab it
				auto found = mp_cells->find(Point(bounds.x + x, bounds.y + y));
				if (found != mp_cells->end())
				{
					cell = found->second;

					// check each entity
					for (auto other : *cell)
					{
						// if no longer in the game, ensure it gets deleted, do not preform operations on it
						if (!mp_registry->valid(other))
						{
							oldEntities.emplace(other);
							continue;
						}

						// if self, ignore
						if (entity == other)
						{
							continue;
						}

						// check if colliding with entity
						Position const& otherPosition = mp_registry->get<Position>(other);
						Collider const& otherCollider = mp_registry->get<Collider>(other);

						// if hitboxes overlap, then there *might* be a collision
						RectF otherHitbox = getWorldHitbox(otherPosition, otherCollider);

						RectF worldOverlap = worldHitbox.overlap(otherHitbox);
						worldOverlap.x += worldHitbox.x;
						worldOverlap.y += worldHitbox.y;

						// if do not overlap, skip to next one
						if (!worldHitbox.overlaps(otherHitbox))
						{
							// if was colliding, now it is not
							if (isInRelationship(entity, other))
							{
								triggerCollisionEndEvent({ entity, &collider, other, &otherCollider, worldOverlap });
								triggerCollisionEndEvent({ other, &otherCollider, entity, &collider, worldOverlap });
							}

							continue;
						}

						// bounding boxes overlap, check masks, if there are masks
						Mask* otherMask = getMask(other, otherCollider);

						if (mask && otherMask)
						{
							// offset by sprite pivots, if able
							PointF otherOffset = getOffset(other);

							RectF offsetHitbox = RectF(worldHitbox.x + offset.x - collider.bounds.x, worldHitbox.y + offset.y - collider.bounds.y, worldHitbox.width, worldHitbox.height);
							RectF otherOffsetHitbox = RectF(otherHitbox.x + otherOffset.x - otherCollider.bounds.x, otherHitbox.y + otherOffset.y - otherCollider.bounds.y, otherHitbox.width, otherHitbox.height);

							// both have a mask, so we can pixel perfect check collisons
							// get slices to check from each mask
							Mask* slice = mask->slice(Rect::round(offsetHitbox.overlap(otherOffsetHitbox)));
							Mask* otherSlice = otherMask->slice(Rect::round(otherOffsetHitbox.overlap(offsetHitbox)));

							// check if no overlap
							if (!slice->collidesWith(*otherSlice))
							{
								// if not colliding, we do not care about it, so skip it

								// done with slices
								delete slice;
								delete otherSlice;

								// if was colliding, now they are not
								// if was colliding, now it is not
								if (isInRelationship(entity, other))
								{
									triggerCollisionEndEvent({ entity, &collider, other, &otherCollider, worldOverlap });
									triggerCollisionEndEvent({ other, &otherCollider, entity, &collider, worldOverlap });
								}

								continue;
							}

							// done with slices
							delete slice;
							delete otherSlice;
						}

						// either is colliding with other via bounding boxes, or via masks
						// in other words... it is colliding with another entity

						// trigger events
						triggerCollisionEnterEvent({ entity, &collider, other, &otherCollider, worldOverlap });
						triggerCollisionEnterEvent({ other, &otherCollider, entity, &collider, worldOverlap });

						// if both things colliding are not triggers, return true
						// if return true, that will tell the collision system that there was a physics collision,
						// thus stopping movement
						// if return false, then there was no physics collision, so keep moving
						if (!collider.isTrigger && !otherCollider.isTrigger)
						{
							collisionDetected = true;
							break;
						}
					}

					// remove entities that are no longer being used
					if (!oldEntities.empty())
					{
						for (int i = cell->size() - 1; i >= 0; i--)
						{
							if (oldEntities.contains(cell->at(i)))
							{
								cell->erase(cell->begin() + i);
							}
						}

						// clear old entities in case we check another cell
						oldEntities.clear();
					}

					// if a collision was detected, stop looping
					if (collisionDetected)
					{
						break;
					}
				}
			}
		}

		// checked all entities, no physics collision here
		return collisionDetected;
	}

	bool PhysicsSystem::isInRelationship(entt::entity const e1, entt::entity const e2)
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

	void PhysicsSystem::addToCell(Point const& pos, entt::entity const entity)
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

	void PhysicsSystem::addToCells(Rect const& cellBounds, entt::entity const entity)
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

	void PhysicsSystem::removeFromCell(Point const& pos, entt::entity const entity)
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

	void PhysicsSystem::removeFromCells(Rect const& cellBounds, entt::entity const entity)
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

	void PhysicsSystem::triggerCollisionEnterEvent(Collision const& collision)
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
	}

	void PhysicsSystem::triggerCollisionEndEvent(Collision const& collision)
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

	Mask* PhysicsSystem::getMask(entt::entity const entity, Collider const& collider) const
	{
		// if collider has a mask, use that
		if (collider.mask)
		{
			return collider.mask;
		}

		// if it doesn't get it from the sprite
		SpriteRenderer* sr = mp_registry->try_get<SpriteRenderer>(entity);

		if (sr && sr->sprite)
		{
			sr->sprite->createMask();
			return sr->sprite->getMask();
		}

		// no mask available
		return nullptr;
	}

	PointF PhysicsSystem::getOffset(entt::entity const entity) const
	{
		SpriteRenderer* sr = mp_registry->try_get<SpriteRenderer>(entity);

		// if there is a sprite, use its offset
		if (sr && sr->sprite)
		{
			return sr->sprite->offset();
		}

		// if no sprite, no offset
		return PointF();
	}

	Rect PhysicsSystem::getCellBounds(RectF const& worldHitbox) const
	{
		return Rect::bounds(
			math_floorToInt(worldHitbox.left() / static_cast<float>(m_cellSize)),
			math_floorToInt(worldHitbox.right() / static_cast<float>(m_cellSize)),
			math_floorToInt(worldHitbox.top() / static_cast<float>(m_cellSize)),
			math_floorToInt(worldHitbox.bottom() / static_cast<float>(m_cellSize)));
	}

	RectF PhysicsSystem::getWorldHitbox(Position const& pos, Collider const& hitbox) const
	{
		Rect hitboxRect = hitbox.bounds;

		return RectF(pos.x + hitboxRect.x, pos.y + hitboxRect.y, static_cast<float>(hitboxRect.width), static_cast<float>(hitboxRect.height));
	}
	
	void PhysicsSystem::updateCellBounds(Collider& collider, RectF const& worldHitbox, entt::entity const entity)
	{
		Rect bounds = getCellBounds(worldHitbox);

		// check if in new bounds
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
	}
}
