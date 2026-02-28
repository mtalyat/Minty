#pragma once
#include "Minty/Physics/Collider.h"
#include "Minty/Library/Bullet.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/DefaultAllocator.h"

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
		inline Any get_native() const override { return mp_root; }

		inline btCollisionShape *get_collision_shape() const { return mp_root; }

		inline btCollisionObject *get_collision_object() const { return mp_object; }

		void bind_collision_object(btCollisionObject *const collisionObject);

	private:
		static void set_static(btCollisionObject &object, Bool const isStatic);

		static void set_trigger(btCollisionObject &object, Bool const isTrigger);

#pragma endregion

#pragma region Variables

	protected:
		btCollisionShape *mp_root;
		btCollisionShape *mp_shape;
		btCollisionObject *mp_object; // a reference to the collision object this collider is attached to
		btTriangleIndexVertexArray *mp_meshInterface; // used for custom mesh colliders

#pragma endregion
	};
}