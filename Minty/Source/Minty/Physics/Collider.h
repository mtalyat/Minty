#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Shape.h"

namespace Minty
{
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
		void* customData = nullptr;

		/// <summary>
		/// The size of the collider.
		/// </summary>
		Float3 size = Math::ONE;
	};

	/// <summary>
	/// A shape that can be used for collision detection in the physics world.
	/// </summary>
	class Collider
	{
#pragma region Variables

	private:
		Shape m_shape;
		Float3 m_size;

#pragma endregion


#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new collider with the given arguments..
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Collider(ColliderBuilder const& builder)
			: m_shape(builder.shape)
			, m_size(builder.size)
		{
		}

		virtual ~Collider()
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Gets the shape of the collider.
		/// </summary>
		/// <returns>The shape of the collider.</returns>
		inline Shape get_shape() const { return m_shape; }

		/// <summary>
		/// Gets the native pointer to the underlying physics object.
		/// </summary>
		/// <returns>The pointer to the native object.</returns>
		virtual void* get_native() const = 0;

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