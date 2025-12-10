#ifndef MINTY_PHYSICS_RIGIDBODY_H
#define MINTY_PHYSICS_RIGIDBODY_H

/**
 * @file RigidBody.h
 * @brief Header file defining the RigidBody class and RigidBodyInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Physics/Force.h"

namespace Minty
{
	struct RigidBodyInfo;

	/**
	 * @brief A physical object that can be moved and interacted with in the physics world.
	 */
	class RigidBody
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new rigid body with the given arguments.
		 * @param info The arguments.
		 */
		RigidBody(RigidBodyInfo const& info);

		virtual ~RigidBody() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets if this rigid body is static.
		 * @return True if static.
		 */
		virtual Bool is_static() const = 0;

		/**
		 * @brief Sets the static state of this rigid body.
		 * @param isStatic True if static.
		 */
		virtual void set_static(Bool const isStatic) = 0;

		/**
		 * @brief Gets if this rigid body is dynamic.
		 * @return True if dynamic.
		 */
		virtual Bool is_dynamic() const = 0;

		/**
		 * @brief Gets if this rigid body is kinematic.
		 * @return True if kinematic.
		 */
		virtual Bool is_kinematic() const = 0;

		/**
		 * @brief Sets the kinematic state of this rigid body.
		 * @param isKinematic True if kinematic.
		 */
		virtual void set_kinematic(Bool const isKinematic) = 0;

		/**
		 * @brief Gets the mass of the rigid body.
		 * @return The mass.
		 */
		virtual Float get_mass() const = 0;

		/**
		 * @brief Sets the mass of the rigid body.
		 * @param mass The mass.
		 */
		virtual void set_mass(Float const mass) = 0;

		/**
		 * @brief Gets the position of the rigid body.
		 * @return The position.
		 */
		virtual Float3 get_position() const = 0;

		/**
		 * @brief Sets the position of the rigid body.
		 * @param position The position.
		 */
		virtual void set_position(Float3 const& position) = 0;

		/**
		 * @brief Gets the rotation of the rigid body.
		 * @return The rotation.
		 */
		virtual Quaternion get_rotation() const = 0;

		/**
		 * @brief Sets the rotation of the rigid body.
		 * @param rotation The rotation.
		 */
		virtual void set_rotation(Quaternion const& rotation) = 0;

		/**
		 * @brief Gets the velocity of the rigid body.
		 * @return The velocity.
		 */
		virtual Float3 get_linear_velocity() const = 0;

		/**
		 * @brief Sets the velocity of the rigid body.
		 * @param velocity The velocity.
		 */
		virtual void set_linear_velocity(Float3 const& velocity) = 0;

		/**
		 * @brief Sets the friction of the rigid body.
		 * @return The friction.
		 */
		virtual Float get_friction() const = 0;

		/**
		 * @brief Gets the friction of the rigid body.
		 * @return The friction.
		 */
		virtual void set_friction(Float const friction) = 0;

		/**
		 * @brief Gets the bounce of the rigid body.
		 * @return The bounce.
		 */
		virtual Float get_bounce() const = 0;

		/**
		 * @brief Sets the bounce of the rigid body.
		 * @param bounce The bounce.
		 */
		virtual void set_bounce(Float const bounce) = 0;

		/**
		 * @brief Gets the native pointer to the underlying physics object.
		 * @return The pointer to the native object.
		 */
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Applies a force to the rigid body.
		 * @param force The force to apply.
		 * @param mode The type of force to apply.
		 */
		virtual void add_force(Float3 const& force, Force const mode) = 0;

		/**
		 * @brief Creates a new RigidBody with the given arguments.
		 * @param info The arguments.
		 * @return A RigidBody Owner.
		 */
		static Shared<RigidBody> create(RigidBodyInfo const& info);

		/**
		 * @brief Creates a default RigidBody.
		 * @return A RigidBody Owner.
		 */
		static Shared<RigidBody> create();

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_RIGIDBODY_H