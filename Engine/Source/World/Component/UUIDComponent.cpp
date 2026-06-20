#include "pch.h"
#include "UUIDComponent.h"
#include "Core/Debug/Debug.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

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