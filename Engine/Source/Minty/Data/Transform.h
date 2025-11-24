#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// Holds position, rotation and scale data.
	/// </summary>
	class Transform
		: public SerializableObject
	{
#pragma region Variables

	private:
		Float3 m_localPosition;
		Quaternion m_localRotation;
		Float3 m_localScale;
		Matrix4 m_globalMatrix;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Transform.
		/// </summary>
		Transform()
			: m_localPosition(0.0f, 0.0f, 0.0f)
			, m_localRotation(Math::identity<Quaternion>())
			, m_localScale(1.0f, 1.0f, 1.0f)
			, m_globalMatrix(Math::identity<Matrix4>())
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		inline Float3 get_local_position() const { return m_localPosition; }

		inline void set_local_position(Float3 const& position)
		{
			m_localPosition = position;
		}

		inline Float3 get_global_position() const
		{
			return Math::extract_position(m_globalMatrix);
		}

		inline Quaternion get_local_rotation() const { return m_localRotation; }

		inline void set_local_rotation(Quaternion const& rotation)
		{
			m_localRotation = rotation;
		}

		inline Quaternion get_global_rotation() const
		{
			return Math::extract_rotation(m_globalMatrix);
		}

		inline Float3 get_local_scale() const { return m_localScale; }

		inline void set_local_scale(Float3 const& scale)
		{
			m_localScale = scale;
		}

		inline Float3 get_global_scale() const
		{
			return Math::extract_scale(m_globalMatrix);
		}

		Matrix4 get_local_matrix() const;

		inline Matrix4 get_global_matrix() const { return m_globalMatrix; }

		inline void set_global_matrix(Matrix4 const& matrix)
		{
			m_globalMatrix = matrix;
		}

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}