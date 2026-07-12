#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Type/Float3.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Matrix4x4.h"

namespace Minty
{
    class Transform
    {
#pragma region Constructor

    public:
        Transform()
            : m_position(Math::ZERO), m_scale(Math::ONE), m_rotation()
        {
        }

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
}