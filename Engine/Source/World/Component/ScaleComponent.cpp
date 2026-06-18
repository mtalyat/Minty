#include "ScaleComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Serializer<ScaleComponent>::serialize(Writer &writer, ScaleComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Serializer<ScaleComponent>::deserialize(Reader &reader, ScaleComponent &value)
{
    reader.read_primary("Scale", value.scale);
    return true;
}
