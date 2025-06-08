#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a RigidBody.
	/// </summary>
	struct RigidBodyBuilder
	{
		/// <summary>
		/// Determines if the rigid body is affected by forces. If true, it is not affected by forces and behaves like a static object.
		/// </summary>
		Bool isKinematic = false;

		/// <summary>
		/// The mass of the object.
		/// </summary>
		Float mass = 1.0f;
	};

	/// <summary>
	/// A physical object that can be moved and interacted with in the physics world.
	/// </summary>
	class RigidBody
	{
#pragma region Variables

	private:
		Bool m_isKinematic;
		Float m_mass = 1.0f;

#pragma endregion


#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new rigid body with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		RigidBody(RigidBodyBuilder const& builder)
			: m_isKinematic(builder.isKinematic)
			, m_mass(builder.mass)
		{
		}

		virtual ~RigidBody()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets if this rigid body is kinematic.
		/// </summary>
		/// <returns>True if kinematic.</returns>
		inline Bool is_kinematic() const { return m_isKinematic; }

		/// <summary>
		/// Sets the kinematic state of this rigid body.
		/// </summary>
		/// <param name="isKinematic">True if kinematic.</param>
		virtual inline void set_kinematic(Bool isKinematic)
		{
			m_isKinematic = isKinematic;
		}

		/// <summary>
		/// Gets the mass of the rigid body.
		/// </summary>
		/// <returns>The mass.</returns>
		inline Float get_mass() const { return m_mass; }

		/// <summary>
		/// Sets the mass of the rigid body.
		/// </summary>
		/// <param name="mass">The mass.</param>
		virtual inline void set_mass(Float mass)
		{
			m_mass = mass;
		}

		/// <summary>
		/// Gets the native pointer to the underlying physics object.
		/// </summary>
		/// <returns>The pointer to the native object.</returns>
		virtual void* get_native() const = 0;

#pragma endregion

#pragma region Methods



#pragma endregion


#pragma region Statics

		/// <summary>
		/// Creates a new RigidBody with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A RigidBody Owner.</returns>
		static Owner<RigidBody> create(RigidBodyBuilder const& builder = {});

#pragma endregion

	};
}