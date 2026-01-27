#include "RotationComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::Serializer<RotationComponent>::serialize(Writer &writer, RotationComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<RotationComponent>::deserialize(Reader &reader, RotationComponent &value)
{
    reader.read_primary("Rotation", value.rotation);
    return true;
}
