#pragma once
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/Collider.h"

namespace Minty
{
	class Bullet_Collider
		: public Collider
	{
#pragma region Variables

	private:
		btCollisionShape* mp_shape;
		btCollisionObject* mp_object;

#pragma endregion

#pragma region Constructors

	public:
		Bullet_Collider(ColliderBuilder const& builder);

		~Bullet_Collider();

#pragma endregion

#pragma region Get Set

	public:
		inline void* get_native() const override { return mp_shape; }

		inline btCollisionShape* get_collision_shape() const { return mp_shape; }

		inline btCollisionObject* get_collision_object() const { return mp_object; }

		inline void set_collision_object(btCollisionObject* object)
		{
			mp_object = object;
		}

#pragma endregion

	};
}