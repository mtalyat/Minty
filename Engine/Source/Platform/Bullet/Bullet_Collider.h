#pragma once
#include "Minty/Physics/Collider.h"
#include "Minty/Library/Bullet.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	/// <summary>
	/// The base class for Bullet Colliders.
	/// </summary>
	class Bullet_Collider
		: public Collider
	{
#pragma region Constructors

	public:
		Bullet_Collider(ColliderInfo const &info);

		~Bullet_Collider() override;

#pragma endregion

#pragma region Accessors

	public:
		inline Any get_native() const override { return mp_object; }

		Float3 get_position() const override;

		void set_position(Float3 const &position) override;

		Quaternion get_rotation() const override;

		void set_rotation(Quaternion const& rotation) override;

		void get_transform(Transform& out_transform) const override;

		void set_transform(Transform const& transform) override;

		inline btCollisionShape *get_collision_shape() const
		{
			return mp_shape;
		}

		inline btCollisionObject *get_collision_object() const
		{
			return mp_object;
		}

		void set_collision_object(btCollisionObject *const object);

#pragma endregion

#pragma region Variables

	protected:
		btCollisionShape *mp_root;
		btCollisionShape *mp_shape;
		btCollisionObject *mp_object;

#pragma endregion
	};
}