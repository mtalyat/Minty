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
		float positionX;
		float positionY;

		int index;

		// float rotation;

		float scaleX;
		float scaleY;

		entt::entity parent;
		std::set<entt::entity>* children;

		Transform()
			: positionX(0.0f)
			, positionY(0.0f)
			, index(0)
			, scaleX(1.0f)
			, scaleY(1.0f)
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
		inline PointF localPosition() const { return PointF(positionX, positionY); }

		/// <summary>
		/// Gets the world position, influenced by the parent.
		/// </summary>
		/// <returns></returns>
		PointF worldPosition(entt::registry const* const registry) const;

		/// <summary>
		/// Gets the local scale.
		/// </summary>
		/// <returns></returns>
		inline PointF localScale() const { return PointF(scaleX, scaleY); }

		/// <summary>
		/// Gets the world scale, influenced by the parent.
		/// </summary>
		/// <returns></returns>
		PointF worldScale(entt::registry const* const registry) const;

		constexpr int localIndex() const { return index; }

		int worldIndex(entt::registry const* const registry) const;

		void setParent(entt::entity const entity, entt::entity const newParentEntity, entt::registry* const registry);

		void setLocalPosition(float const x, float const y);

		void setWorldPosition(float const x, float const y, entt::registry* const registry);

		void setLocalScale(float const x, float const y);

		void setWorldScale(float const x, float const y, entt::registry* const registry);

		void setLocalIndex(int const i);

		void setWorldIndex(int const i, entt::registry* const registry);

		void detach(entt::entity const entity, entt::registry* const registry);

		void detachFromParent(entt::entity const entity, entt::registry* const registry);

		void detachFromChildren(entt::entity const entity, entt::registry* const registry);
	};
}