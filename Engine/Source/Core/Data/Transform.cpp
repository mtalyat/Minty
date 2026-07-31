#include "pch.hpp"
#include "Transform.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Minty::Transform::Transform()
            : m_position(Math::ZERO), m_scale(Math::ONE), m_rotation()
        {
        }

        Minty::Transform::Transform(Float3 const &position)
            : m_position(position), m_scale(Math::ONE), m_rotation(), m_dirty(true)
        {
        }

        Minty::Transform::Transform(Float3 const &position, Float3 const &scale)
            : m_position(position), m_scale(scale), m_rotation(), m_dirty(true)
        {
        }

        Minty::Transform::Transform(Float3 const &position, Float3 const &scale, Quaternion const &rotation)
            : m_position(position), m_scale(scale), m_rotation(rotation), m_dirty(true)
        {
        }

void Minty::Serializer<Transform>::serialize(Writer &writer, Transform const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Transform>::deserialize(Reader &reader, Transform &value)
{
    Bool modified = false;

    modified |= reader.read("Position", value.m_position);
    modified |= reader.read("Scale", value.m_scale);
    modified |= reader.read("Rotation", value.m_rotation);

    if (modified)
    {
        value.m_dirty = true;
    }

    return true;
}
