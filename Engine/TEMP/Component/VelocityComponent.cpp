#include "VelocityComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<VelocityComponent>::serialize(Writer &writer, VelocityComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<VelocityComponent>::deserialize(Reader &reader, VelocityComponent &value)
{
    reader.read_primary("Velocity", value.velocity);
    return true;
}
