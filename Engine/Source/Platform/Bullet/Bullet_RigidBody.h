#pragma once
#include "Minty/Data/Pointer.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/Rigidbody.h"

namespace Minty
{
	class Bullet_Rigidbody
		: public Rigidbody
	{
#pragma region Constructors

	public:
		Bullet_Rigidbody(RigidbodyInfo const& info);

		~Bullet_Rigidbody();

#pragma endregion

#pragma region Accessors

	public:
		inline Any get_native() const override { return mp_body; }

		inline btRigidBody* get_rigidbody() const { return mp_body; }

		// set and update values to the given body
		void bind_rigidbody(btRigidBody* const body);

		void set_static(Bool const isStatic) override;

		void set_kinematic(Bool const isKinematic) override;

		void set_mass(Float const mass) override;

		void set_linear_damping(Float const linearDamping) override;

		void set_angular_damping(Float const angularDamping) override;

		void set_rotation_constraints(Constraints const constraints) override;

		Float3 get_simulation_position() const override;

		void set_simulation_position(Float3 const& position) override;

		Quaternion get_simulation_rotation() const override;

		void set_simulation_rotation(Quaternion const& rotation) override;

		Float3 get_simulation_linear_velocity() const override;

		void set_simulation_linear_velocity(Float3 const& velocity) override;

#pragma endregion

#pragma region Methods

	public:
		void add_force(Float3 const& force, Force const mode) override;

	private:
		static void set_static(btRigidBody& body, Bool const isStatic);

		static void set_kinematic(btRigidBody& body, Bool const isKinematic);

		static void set_mass(btRigidBody& body, Float const mass);

		static void set_rotation_constraints(btRigidBody& body, Constraints const constraints);

		static void set_damping(btRigidBody& body, Float const linearDamping, Float const angularDamping);

#pragma endregion

#pragma region Variables

	private:
		btRigidBody* mp_body;

#pragma endregion
	};
}