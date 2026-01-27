#include "GravityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<GravityComponent>::serialize(Writer &writer, GravityComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<GravityComponent>::deserialize(Reader &reader, GravityComponent &value)
{
    reader.read_primary("Scale", value.scale);
    return true;
}
