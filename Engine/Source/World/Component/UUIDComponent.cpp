#include "pch.hpp"
#include "UUIDComponent.hpp"
#include "Core/Debug/Debug.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<UUIDComponent>::serialize(Writer &writer, UUIDComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<UUIDComponent>::deserialize(Reader &reader, UUIDComponent &value)
{
    reader.read_primary("ID", value.id);
    return true;
}