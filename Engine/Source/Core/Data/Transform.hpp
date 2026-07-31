#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Float3.hpp"
#include "Core/Math/Quaternion.hpp"
#include "Core/Math/Matrix4x4.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    class Transform
    {
        friend struct Serializer<Transform>;

#pragma region Constructor

    public:
        Transform();

        Transform(Float3 const &position);

        Transform(Float3 const &position, Float3 const &scale);

        Transform(Float3 const &position, Float3 const &scale, Quaternion const &rotation);

#pragma endregion

#pragma region Accessors

    public:
        void set_position(Float3 const &position)
        {
            m_position = position;
            m_dirty = true;
        }

        void set_scale(Float3 const &scale)
        {
            m_scale = scale;
            m_dirty = true;
        }

        void set_rotation(Quaternion const &rotation)
        {
            m_rotation = rotation;
            m_dirty = true;
        }

        Float3 const &get_position() const
        {
            return m_position;
        }

        Float3 const &get_scale() const
        {
            return m_scale;
        }

        Quaternion const &get_rotation() const
        {
            return m_rotation;
        }

        Matrix4 const &get_local_matrix() const
        {
            if (m_dirty)
            {
                m_local = Math::translate(Math::identity<Matrix4>(), m_position) *
                          Math::to_matrix(m_rotation) *
                          Math::scale(Math::identity<Matrix4>(), m_scale);
                m_dirty = false;
            }
            return m_local;
        }

        Matrix4 const& get_global_matrix() const
        {
            // TODO: get actual global matrix
            return get_local_matrix();
        }

#pragma endregion

#pragma region Variables

    private:
        Float3 m_position;
        Float3 m_scale;
        Quaternion m_rotation;

        // cached matrices for local and global transforms
        Matrix4 mutable m_local;
        Bool mutable m_dirty;

#pragma endregion
    };
    
	template<>
	struct Serializer<Transform>
	{
		static void serialize(Writer& writer, Transform const& value);
		static Bool deserialize(Reader& reader, Transform& value);
	};
}