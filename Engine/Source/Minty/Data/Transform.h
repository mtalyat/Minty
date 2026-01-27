#ifndef MINTY_DATA_TRANSFORM_H
#define MINTY_DATA_TRANSFORM_H

/**
 * @file Transform.h
 * @brief Defines the Transform class for position, rotation, and scale data.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @class Transform
	 * @brief Represents the position, rotation, and scale of an object in 3D space.
	 */
	class Transform
	{
		friend struct Serializer<Transform>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Transform with default values.
		 */
		Transform();

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the local position of the Transform.
		 * @returns The local position.
		 */
		inline Float3 get_local_position() const { return m_localPosition; }

		/**
		 * @brief Sets the local position of the Transform.
		 * @param position The new local position.
		 */
		inline void set_local_position(Float3 const& position) { m_localPosition = position; }

		/**
		 * @brief Gets the global position of the Transform.
		 * @returns The global position.
		 */
		inline Float3 get_global_position() const { return Math::extract_position(m_globalMatrix); }

		/**
		 * @brief Gets the local rotation of the Transform.
		 * @returns The local rotation.
		 */
		inline Quaternion get_local_rotation() const { return m_localRotation; }

		/**
		 * @brief Sets the local rotation of the Transform.
		 * @param rotation The new local rotation.
		 */
		inline void set_local_rotation(Quaternion const& rotation) { m_localRotation = rotation; }

		/**
		 * @brief Gets the global rotation of the Transform.
		 * @returns The global rotation.
		 */
		inline Quaternion get_global_rotation() const { return Math::extract_rotation(m_globalMatrix); }

		/**
		 * @brief Gets the local scale of the Transform.
		 * @returns The local scale.
		 */
		inline Float3 get_local_scale() const { return m_localScale; }

		/**
		 * @brief Sets the local scale of the Transform.
		 * @param scale The new local scale.
		 */
		inline void set_local_scale(Float3 const& scale) { m_localScale = scale; }

		/**
		 * @brief Gets the global scale of the Transform.
		 * @returns The global scale.
		 */
		inline Float3 get_global_scale() const { return Math::extract_scale(m_globalMatrix); }

		/**
		 * @brief Gets the local transformation matrix of the Transform.
		 * @returns The local transformation matrix.
		 */
		Matrix4 get_local_matrix() const;

		/**
		 * @brief Gets the global transformation matrix of the Transform.
		 * @returns The global transformation matrix.
		 */
		inline Matrix4 get_global_matrix() const { return m_globalMatrix; }

		/**
		 * @brief Sets the global transformation matrix of the Transform.
		 * @param matrix The new global transformation matrix.
		 */
		inline void set_global_matrix(Matrix4 const& matrix) { m_globalMatrix = matrix; }

#pragma endregion

#pragma region Variables

	private:
		Float3 m_localPosition;
		Quaternion m_localRotation;
		Float3 m_localScale;
		Matrix4 m_globalMatrix;

#pragma endregion
	};

	template<>
	struct Serializer<Transform>
	{
		static void serialize(Writer& writer, Transform const& value);
		static Bool deserialize(Reader& reader, Transform& value);
	};
}

#endif // MINTY_DATA_TRANSFORM_H