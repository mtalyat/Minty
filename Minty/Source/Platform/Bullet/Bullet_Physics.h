#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Transform.h"
#include "Minty/Library/Bullet.h"

namespace Minty
{
	class Bullet_Physics
	{
#pragma region Constructors

	private:
		Bullet_Physics() = default;
		~Bullet_Physics() = default;

#pragma endregion

#pragma region Statics

	public:
		static btTransform to_bullet(Transform const& transform)
		{
			btTransform btTransform;
			btTransform.setIdentity();
			btTransform.setOrigin(to_bullet(transform.get_global_position()));
			btTransform.setRotation(to_bullet(transform.get_global_rotation()));
			return btTransform;
		}

		inline static btVector3 to_bullet(Float3 const& vector)
		{
			return btVector3(vector.x, vector.y, vector.z);
		}

		inline static btQuaternion to_bullet(Quaternion const& quaternion)
		{
			return btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
		}

#pragma endregion

	};
}