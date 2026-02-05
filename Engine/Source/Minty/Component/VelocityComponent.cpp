#include "VelocityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<VelocityComponent>::serialize(Writer &writer, VelocityComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<VelocityComponent>::deserialize(Reader &reader, VelocityComponent &value)
{
    reader.read_primary("Velocity", value.velocity);
    return true;
}
