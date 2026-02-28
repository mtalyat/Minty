#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Transform.h"
#include "Minty/Library/Bullet.h"

namespace Minty
{
	class PhysicsMaterial;

	class Bullet_Physics
	{
#pragma region Constructors

	private:
		Bullet_Physics() = default;
		~Bullet_Physics() = default;

#pragma endregion

#pragma region Methods

#pragma region Minty -> Bullet

	public:
		static btTransform to_bullet(Transform const &transform);

		inline static btVector3 to_bullet(Float3 const &vector)
		{
			return btVector3(vector.x, vector.y, vector.z);
		}

		inline static btQuaternion to_bullet(Quaternion const &quaternion)
		{
			return btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
		}

#pragma endregion

#pragma region Bullet -> Minty

	public:
		inline static Float3 to_minty(btVector3 const &vector)
		{
			return Float3(vector.x(), vector.y(), vector.z());
		}

		inline static Quaternion to_minty(btQuaternion const &quaternion)
		{
			return Quaternion(quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w());
		}

#pragma endregion

#pragma endregion
	};
}