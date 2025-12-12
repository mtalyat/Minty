#ifndef MINTY_PHYSICS_COLLIDER_H
#define MINTY_PHYSICS_COLLIDER_H

/**
 * @file Collider.h
 * @brief Header file defining the Collider class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Shape.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	class Mesh;
	struct ColliderInfo;

	/**
	 * @brief The base class for all physics Colliders.
	 */
	class Collider
		: public SerializableObject
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new collider with the given arguments.
		 * @param info The arguments.
		 */
		Collider(ColliderInfo const& info);

		virtual ~Collider() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this Collider is static.
		 * @return True if static, otherwise false.
		 */
		inline Bool is_static() const { return m_isStatic; }

		/**
		 * @brief Gets the Shape of this Collider.
		 * @return The Shape.
		 */
		inline Shape get_shape() const { return m_shape; }

		/**
		 * @brief Gets the offset of this Collider.
		 * @return The offset.
		 */
		inline Float3 const& get_offset() const { return m_offset; }

		/**
		 * @brief Gets the size of this Collider.
		 * @return The size.
		 */
		inline Float3 const& get_size() const { return m_size; }

		/**
		 * @brief Gets the Mesh used for this Collider if the Shape is Custom.
		 * @return The Mesh Owner.
		 */
		inline Shared<Mesh> const& get_mesh() const { return m_mesh; }

		/**
		 * @brief Gets the native pointer to the underlying physics object.
		 * @return The pointer to the native object.
		 */
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

		/**
		 * @brief Creates a new Collider with the given arguments.
		 * @param info The arguments.
		 * @return A Collider Owner.
		 */
		static Shared<Collider> create(ColliderInfo const& info);

		/**
		 * @brief Creates a default Collider (Box shape, size (1,1,1), non-static).
		 * @return A Collider Owner.
		 */
		static Shared<Collider> create();

#pragma endregion

#pragma region Variables

	private:
		Shape m_shape;
		Shared<Mesh> m_mesh; // only used if shape is Custom
		Float3 m_offset;
		Float3 m_size;
		Bool m_isStatic;

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_COLLIDER_H