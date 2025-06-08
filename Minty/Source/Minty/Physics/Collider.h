#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Shape.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	class Mesh;

	/// <summary>
	/// The arguments for a Collider.
	/// </summary>
	struct ColliderBuilder
	{
		/// <summary>
		/// The shape of the collider.
		/// </summary>
		Shape shape = Shape::Empty;

		/// <summary>
		/// The data for a custom Shape.
		/// </summary>
		Ref<Mesh> mesh = nullptr;

		/// <summary>
		/// The size of the collider.
		/// </summary>
		Float3 size = Math::ONE;

		/// <summary>
		/// If the Collider is static or not. 
		/// If static, it cannot move, rotate, deform, or have a RigidBody.
		/// </summary>
		Bool isStatic = false;
	};

	/// <summary>
	/// The base class for all physics Colliders.
	/// </summary>
	class Collider
		: public SerializableObject
	{
#pragma region Variables

	private:
		Shape m_shape;
		Ref<Mesh> m_mesh; // only used if shape is Custom
		Float3 m_size;
		Bool m_isStatic;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new collider with the given arguments..
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Collider(ColliderBuilder const& builder)
			: m_shape(builder.shape)
			, m_mesh(builder.mesh)
			, m_size(builder.size)
			, m_isStatic(builder.isStatic)
		{
		}

		virtual ~Collider()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Shape of this Collider.
		/// </summary>
		/// <returns>The Shape.</returns>
		inline Shape get_shape() const { return m_shape; }

		/// <summary>
		/// Checks if this Collider is static.
		/// </summary>
		/// <returns>True if static, otherwise false.</returns>
		inline Bool is_static() const { return m_isStatic; }

		/// <summary>
		/// Gets the native pointer to the underlying physics object.
		/// </summary>
		/// <returns>The pointer to the native object.</returns>
		virtual void* get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Statics

		/// <summary>
		/// Creates a new Collider with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A Collider Owner.</returns>
		static Owner<Collider> create(ColliderBuilder const& builder = {});

#pragma endregion
	};
}