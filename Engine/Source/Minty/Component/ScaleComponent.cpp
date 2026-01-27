#include "ScaleComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Serializer<ScaleComponent>::serialize(Writer &writer, ScaleComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Serializer<ScaleComponent>::deserialize(Reader &reader, ScaleComponent &value)
{
    reader.read_primary("Scale", value.scale);
    return true;
}
