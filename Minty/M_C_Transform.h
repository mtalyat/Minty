#pragma once

#include "M_Main.h"
#include "M_PointF.h"
#include "entt.hpp"
#include <set>

namespace minty
{
	/// <summary>
	/// Transforms hold all of the positional, rotational and spacial data in regards to an entity.
	/// </summary>
	struct MINTY_API Transform
	{
		float localPosX;
		float localPosY;
		float worldPosX;
		float worldPosY;

		int zIndex;

		// float rotation;

		float localSizeX;
		float localSizeY;
		float worldSizeX;
		float worldSizeY;

		entt::entity parent;
		std::set<entt::entity>* children;

		Transform()
			: localPosX(0.0f)
			, localPosY(0.0f)
			, worldPosX(0.0f)
			, worldPosY(0.0f)
			, zIndex(0)
			, localSizeX(1.0f)
			, localSizeY(1.0f)
			, worldSizeX(1.0f)
			, worldSizeY(1.0f)
			, parent(entt::null)
			, children(nullptr)
		{}

		~Transform()
		{
			if (children)
			{
				delete children;
			}
		}

		/// <summary>
		/// Gets the local position.
		/// </summary>
		/// <returns></returns>
		PointF localPosition() const { return PointF(localPosX, localPosY); }

		/// <summary>
		/// Gets the world position, influenced by the parent.
		/// </summary>
		/// <returns></returns>
		PointF worldPosition() const { return PointF(worldPosX, worldPosY); }

		/// <summary>
		/// Gets the local size.
		/// </summary>
		/// <returns></returns>
		PointF localSize() const { return PointF(localSizeX, localSizeY); }

		/// <summary>
		/// Gets the world size, influenced by the parent.
		/// </summary>
		/// <returns></returns>
		PointF worldSize() const { return PointF(worldSizeX, worldSizeY); }

		void setParent(entt::entity const entity, entt::entity const newParentEntity, entt::registry* const registry);

		void setLocalPosition(entt::entity const entity, float const x, float const y, entt::registry* const registry);

		void setWorldPosition(entt::entity const entity, float const x, float const y, entt::registry* const registry);

		void updatePosition(Transform const* const parentTransform, entt::registry* const registry);

		void updatePosition(entt::registry* const registry);
	};
}