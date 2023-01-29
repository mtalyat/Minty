#include "pch.h"
#include "M_C_Transform.h"

namespace minty
{
	void Transform::setParent(entt::entity const entity, entt::entity const newParentEntity, entt::registry* const registry)
	{
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
	}

	void Transform::setLocalPosition(entt::entity const entity, float const x, float const y, entt::registry* const registry)
	{
		localPosX = x;
		localPosY = y;

		updatePosition(registry);
	}

	void Transform::setWorldPosition(entt::entity const entity, float const x, float const y, entt::registry* const registry)
	{
		if (registry->valid(parent))
		{
			Transform* parentTransform = &registry->get<Transform>(parent);

			if (parentTransform->worldSizeX != 0.0f && parentTransform->worldSizeY != 0.0f)
			{
				localPosX = (x - parentTransform->worldPosX) / parentTransform->worldSizeX;
				localPosY = (y - parentTransform->worldPosY) / parentTransform->worldSizeY;

				updatePosition(parentTransform, registry);
			}
		}
		else
		{
			localPosX = x;
			localPosY = y;

			updatePosition(nullptr, registry);
		}
	}

	void Transform::updatePosition(Transform const* const parent, entt::registry* const registry)
	{
		// get position from parent
		// update based on that

		if (parent)
		{
			worldPosX = parent->worldPosX + parent->worldSizeX * localPosX;
			worldPosY = parent->worldPosY + parent->worldSizeY * localPosY;

			worldSizeX = parent->worldSizeX * localSizeX;
			worldSizeY = parent->worldSizeY * localSizeY;
		}
		else
		{
			worldPosX = localPosX;
			worldPosY = localPosY;

			worldSizeX = localSizeX;
			worldSizeY = localSizeY;
		}

		// set position based on parent pos and size


		// update children
		if (children)
		{
			for (auto entity : *children)
			{
				registry->get<Transform>(entity).updatePosition(this, registry);
			}
		}
	}

	void Transform::updatePosition(entt::registry* const registry)
	{
		if (registry->valid(parent))
		{
			Transform* parentTransform = &registry->get<Transform>(parent);

			updatePosition(parentTransform, registry);
		}
		else
		{
			updatePosition(nullptr, registry);
		}		
	}
}
