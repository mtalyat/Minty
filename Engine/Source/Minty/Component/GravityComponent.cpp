#include "GravityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<GravityComponent>::serialize(Writer &writer, GravityComponent const &value)
{
    writer.write("Scale", value.scale);
}

void Minty::Serializer<GravityComponent>::deserialize(Reader &reader, GravityComponent &value)
{
    if(!reader.read_default(value.scale))
    {
        reader.read("Scale", value.scale);
    }
}
