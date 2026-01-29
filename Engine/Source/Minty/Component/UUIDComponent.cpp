#include "pch.h"
#include "UUIDComponent.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

void Minty::Serializer<UUIDComponent>::serialize(Writer &writer, UUIDComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<UUIDComponent>::deserialize(Reader &reader, UUIDComponent &value)
{
    reader.read_primary("ID", value.id);
    return true;
}