#include "GravityComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<GravityComponent>::serialize(Writer &writer, GravityComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<GravityComponent>::deserialize(Reader &reader, GravityComponent &value)
{
    reader.read_primary("Scale", value.scale);
    return true;
}
