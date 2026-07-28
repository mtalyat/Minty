#include "pch.hpp"
#include "Transform.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

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
