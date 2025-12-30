#include "ScaleComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Serializer<ScaleComponent>::serialize(Writer &writer, ScaleComponent const &value)
{
    writer.write("Scale", value.scale);
}

void Serializer<ScaleComponent>::deserialize(Reader &reader, ScaleComponent &value)
{
    reader.read("Scale", value.scale);
}
