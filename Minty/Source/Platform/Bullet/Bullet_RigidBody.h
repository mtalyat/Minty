#pragma once
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	class Bullet_RigidBody
		: public RigidBody
	{
#pragma region Variables

	private:
		btRigidBody* mp_body = nullptr;

#pragma endregion

#pragma region Constructors

	public:
		Bullet_RigidBody(RigidBodyBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		inline void* get_native() const override { return mp_body; }

		inline btRigidBody* get_rigid_body() const { return mp_body; }

		inline void set_rigid_body(btRigidBody* body)
		{
			mp_body = body;
		}

#pragma endregion

	};
}