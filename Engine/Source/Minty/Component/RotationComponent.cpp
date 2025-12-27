#include "RotationComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<RotationComponent>::serialize(Writer &writer, RotationComponent const &value)
{
    writer.write("Rotation", value.rotation);
}

void Minty::Serializer<RotationComponent>::deserialize(Reader &reader, RotationComponent &value)
{
    if(!reader.read_default(value.rotation))
    {
        reader.read("Rotation", value.rotation);
    }
}
