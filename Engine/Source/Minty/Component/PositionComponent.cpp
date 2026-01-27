#include "PositionComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<PositionComponent>::serialize(Writer &writer, PositionComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<PositionComponent>::deserialize(Reader &reader, PositionComponent &value)
{
    reader.read_primary("Position", value.position);
    return true;
}
