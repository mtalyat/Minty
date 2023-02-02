#include "pch.h"
#include "M_C_Transform.h"

namespace minty
{
	PointF Transform::worldPosition(entt::registry const* const registry) const
	{
		// if parent, use parent's values
		if (registry->valid(parent))
		{
			Transform const& parentTransform = registry->get<Transform>(parent);

			PointF parentPos = parentTransform.worldPosition(registry);
			PointF parentScale = parentTransform.worldScale(registry);

			return PointF(parentPos.x + positionX * parentScale.x, parentPos.y + positionY * parentScale.y);
		}

		return localPosition();
	}

	PointF Transform::worldScale(entt::registry const* const registry) const
	{
		// if parent, use parent's values
		if (registry->valid(parent))
		{
			PointF parentWorldScale = registry->get<Transform>(parent).worldScale(registry);

			return PointF(parentWorldScale.x * scaleX, parentWorldScale.y * scaleY);
		}

		return localScale();
	}

	int Transform::worldIndex(entt::registry const* const registry) const
	{
		// if parent, use parent's values
		if (registry->valid(parent))
		{
			return registry->get<Transform>(parent).worldIndex(registry) + index;
		}

		return localIndex();
	}

	void Transform::setParent(entt::entity const entity, entt::entity const newParentEntity, entt::registry* const registry)
	{
		// get world position
		PointF worldPos = worldPosition(registry);

		// remove from old parent list
		if (registry->valid(parent))
		{
			Transform& parentTransform = registry->get<Transform>(parent);

			if (parentTransform.children)
			{
				parentTransform.children->erase(entity);
			}
		}

		// set parent
		parent = newParentEntity;

		// add to new parent list
		if (registry->valid(parent))
		{
			Transform& newParentTransform = registry->get<Transform>(parent);

			if (!newParentTransform.children)
			{
				newParentTransform.children = new std::set<entt::entity>();
			}

			newParentTransform.children->emplace(entity);
		}

		// set new world pos
		setWorldPosition(worldPos.x, worldPos.y, registry);
	}

	void Transform::setLocalPosition(float const x, float const y)
	{
		positionX = x;
		positionY = y;
	}

	void Transform::setWorldPosition(float const x, float const y, entt::registry* const registry)
	{
		if (registry->valid(parent))
		{
			Transform const& parentTransform = registry->get<Transform>(parent);

			PointF parentSize = parentTransform.worldScale(registry);

			if (parentSize.x != 0.0f && parentSize.y != 0.0f)
			{
				PointF parentPos = parentTransform.worldPosition(registry);

				positionX = (x - parentPos.x) / parentSize.x;
				positionY = (y - parentPos.y) / parentSize.y;
			}
			else
			{
				// parent size = 0, so ignore?
			}
		}
		else
		{
			setLocalPosition(x, y);
		}
	}

	void Transform::setLocalScale(float const x, float const y)
	{
		scaleX = x;
		scaleY = y;
	}

	void Transform::setWorldScale(float const x, float const y, entt::registry* const registry)
	{
		if (registry->valid(parent))
		{
			PointF parentSize = registry->get<Transform>(parent).worldScale(registry);

			scaleX = x * parentSize.x;
			scaleY = y * parentSize.y;
		}
		else
		{
			setLocalScale(x, y);
		}
	}

	void Transform::setLocalIndex(int const i)
	{
		index = i;
	}

	void Transform::setWorldIndex(int const i, entt::registry* const registry)
	{
		if (registry->valid(parent))
		{
			index = i - registry->get<Transform>(parent).worldIndex(registry);
		}
		else
		{
			index = i;
		}
	}

	void Transform::detach(entt::entity const entity, entt::registry* const registry)
	{
		// remove children
		detachFromChildren(entity, registry);
		detachFromParent(entity, registry);
	}

	void Transform::detachFromParent(entt::entity const entity, entt::registry* const registry)
	{
		// if parent, remove this entity from its children
		if (registry->valid(parent))
		{
			Transform& parentTransform = registry->get<Transform>(parent);

			parentTransform.children->erase(entity);

			setParent(entity, entt::null, registry);
		}
	}

	void Transform::detachFromChildren(entt::entity const entity, entt::registry* const registry)
	{
		if (children)
		{
			for (auto child : *children)
			{
				Transform& childTransform = registry->get<Transform>(child);

				childTransform.setParent(child, entt::null, registry);
			}

			children->clear();
		}
	}
}
