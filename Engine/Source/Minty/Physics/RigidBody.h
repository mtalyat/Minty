#ifndef MINTY_PHYSICS_RIGIDBODY_H
#define MINTY_PHYSICS_RIGIDBODY_H

/**
 * @file Rigidbody.h
 * @brief Header file defining the Rigidbody class and RigidbodyInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/Constraints.h"
#include "Minty/Physics/Force.h"

namespace Minty
{
	struct RigidbodyInfo;

	/**
	 * @brief A physical object that can be moved and interacted with in the physics world.
	 */
	class Rigidbody
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new rigid body with the given arguments.
		 * @param info The arguments.
		 */
		Rigidbody(RigidbodyInfo const& info);

		virtual ~Rigidbody() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets if this rigid body is static.
		 * @return True if static.
		 */
		inline Bool is_static() const { return m_isStatic; }

		/**
		 * @brief Sets the static state of this rigid body.
		 * @param isStatic True if static.
		 */
		inline virtual void set_static(Bool const isStatic) { m_isStatic = isStatic; }

		/**
		 * @brief Gets if this rigid body is dynamic.
		 * @return True if dynamic.
		 */
		inline Bool is_dynamic() const { return !m_isStatic && !m_isKinematic; }

		/**
		 * @brief Gets if this rigid body is kinematic.
		 * @return True if kinematic.
		 */
		inline Bool is_kinematic() const { return m_isKinematic; }

		/**
		 * @brief Sets the kinematic state of this rigid body.
		 * @param isKinematic True if kinematic.
		 */
		inline virtual void set_kinematic(Bool const isKinematic) { m_isKinematic = isKinematic; }

		/**
		 * @brief Gets the mass of the rigid body.
		 * @return The mass.
		 */
		inline Float get_mass() const { return m_mass; }

		/**
		 * @brief Sets the mass of the rigid body.
		 * @param mass The mass.
		 */
		virtual void set_mass(Float const mass);

		/**
		 * @brief Gets the constraints applied to the rigid body.
		 * @return The constraints.
		 */
		inline Constraints get_rotation_constraints() const { return m_rotationConstraints; }

		/**
		 * @brief Sets the constraints applied to the rigid body.
		 * @param constraints The constraints.
		 */
		inline virtual void set_rotation_constraints(Constraints const constraints) { m_rotationConstraints = constraints; }

		/**
		 * @brief Gets the position of the rigid body.
		 * @return The position.
		 */
		virtual Float3 get_simulation_position() const = 0;

		/**
		 * @brief Sets the position of the rigid body.
		 * @param position The position.
		 */
		virtual void set_simulation_position(Float3 const& position) = 0;

		/**
		 * @brief Gets the rotation of the rigid body.
		 * @return The rotation.
		 */
		virtual Quaternion get_simulation_rotation() const = 0;

		/**
		 * @brief Sets the rotation of the rigid body.
		 * @param rotation The rotation.
		 */
		virtual void set_simulation_rotation(Quaternion const& rotation) = 0;

		/**
		 * @brief Gets the velocity of the rigid body.
		 * @return The velocity.
		 */
		virtual Float3 get_simulation_linear_velocity() const = 0;

		/**
		 * @brief Sets the velocity of the rigid body.
		 * @param velocity The velocity.
		 */
		virtual void set_simulation_linear_velocity(Float3 const& velocity) = 0;

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
		 * @brief Creates a new Rigidbody with the given arguments.
		 * @param info The arguments.
		 * @return A Rigidbody Owner.
		 */
		static Shared<Rigidbody> create(RigidbodyInfo const& info);

		/**
		 * @brief Creates a default Rigidbody.
		 * @return A Rigidbody Owner.
		 */
		static Shared<Rigidbody> create();

#pragma endregion

#pragma region Variables

	public:
		Constraints m_rotationConstraints;
		Float m_mass;
		Bool m_isKinematic;
		Bool m_isStatic;

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_RIGIDBODY_H