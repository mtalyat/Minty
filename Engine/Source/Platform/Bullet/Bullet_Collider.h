#pragma once
#include "Minty/Physics/Collider.h"
#include "Minty/Library/Bullet.h"

namespace Minty
{
	/// <summary>
	/// The base class for Bullet Colliders.
	/// </summary>
	class Bullet_Collider
		: public Collider
	{
#pragma region Variables

	protected:
		btCollisionShape* mp_shape;
		btCollisionObject* mp_object;

#pragma endregion

#pragma region Constructors

	public:
		Bullet_Collider(ColliderBuilder const& builder)
			: Collider(builder)
			, mp_shape(nullptr)
			, mp_object(nullptr)
		{
		}

		virtual ~Bullet_Collider()
		{
			delete mp_shape;
			delete mp_object;
		}

#pragma endregion

#pragma region Get Set

	public:
		inline void* get_native() const override { return mp_shape; }

		inline btCollisionShape* get_collision_shape() const
		{
			return mp_shape;
		}

		inline btCollisionObject* get_collision_object() const
		{
			return mp_object;
		}

		inline void set_collision_object(btCollisionObject* object)
		{
			mp_object = object;
		}

#pragma endregion

	};
}