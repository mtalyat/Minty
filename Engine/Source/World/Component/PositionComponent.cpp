#include "PositionComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<PositionComponent>::serialize(Writer &writer, PositionComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<PositionComponent>::deserialize(Reader &reader, PositionComponent &value)
{
    reader.read_primary("Position", value.position);
    return true;
}
