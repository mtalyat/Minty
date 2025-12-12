#pragma once
#include "Minty/Data/Pointer.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	class Bullet_RigidBody
		: public RigidBody
	{
#pragma region Constructors

	public:
		Bullet_RigidBody(RigidBodyInfo const& info);

		~Bullet_RigidBody();

#pragma endregion

#pragma region Accessors

	public:
		inline Any get_native() const override { return mp_body; }

		Bool is_static() const override;

		void set_static(Bool const isStatic) override;

		Bool is_dynamic() const override;

		Bool is_kinematic() const override;

		void set_kinematic(Bool const isKinematic) override;
		
		Float get_mass() const override;

		void set_mass(Float const mass) override;

		Float3 get_position() const override;

		void set_position(Float3 const& position) override;

		Quaternion get_rotation() const override;

		void set_rotation(Quaternion const& rotation) override;

		Float3 get_linear_velocity() const override;

		void set_linear_velocity(Float3 const& velocity) override;
	
		Float get_friction() const override;
		
		void set_friction(Float const friction) override;
		
		Float get_bounce() const override;
		
		void set_bounce(Float const bounce) override;

		Constraints get_constraints() const override;

		void set_rotation_constraints(Constraints const constraints) override;

		void set_entity(Entity const entity);

		Entity get_entity() const;

#pragma endregion

#pragma region Methods

	public:
		void add_force(Float3 const& force, Force const mode) override;

#pragma endregion

#pragma region Variables

	private:
		btRigidBody* mp_body;

#pragma endregion
	};
}