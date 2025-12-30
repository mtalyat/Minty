#include "VelocityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<VelocityComponent>::serialize(Writer &writer, VelocityComponent const &value)
{
    writer.write("Velocity", value.velocity);
}

void Minty::Serializer<VelocityComponent>::deserialize(Reader &reader, VelocityComponent &value)
{
    reader.read("Velocity", value.velocity);
}
