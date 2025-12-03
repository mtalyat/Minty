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
		 * @brief Gets if this rigid body is kinematic.
		 * @return True if kinematic.
		 */
		inline Bool is_kinematic() const { return m_isKinematic; }

		/**
		 * @brief Sets the kinematic state of this rigid body.
		 * @param isKinematic True if kinematic.
		 */
		inline virtual void set_kinematic(Bool isKinematic) { m_isKinematic = isKinematic; }

		/**
		 * @brief Gets the mass of the rigid body.
		 * @return The mass.
		 */
		inline Float get_mass() const { return m_mass; }

		/**
		 * @brief Sets the mass of the rigid body.
		 * @param mass The mass.
		 */
		inline virtual void set_mass(Float mass) { m_mass = mass; }

		/**
		 * @brief Gets the native pointer to the underlying physics object.
		 * @return The pointer to the native object.
		 */
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Methods

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

#pragma region Variables

	private:
		Bool m_isKinematic;
		Float m_mass = 1.0f;

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_RIGIDBODY_H