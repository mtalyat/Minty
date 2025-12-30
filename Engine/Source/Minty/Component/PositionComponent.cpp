#include "PositionComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<PositionComponent>::serialize(Writer &writer, PositionComponent const &value)
{
    writer.write("Position", value.position);
}

void Minty::Serializer<PositionComponent>::deserialize(Reader &reader, PositionComponent &value)
{
    reader.read("Position", value.position);
}
