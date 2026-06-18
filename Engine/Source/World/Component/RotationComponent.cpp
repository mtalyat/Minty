#include "RotationComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<RotationComponent>::serialize(Writer &writer, RotationComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<RotationComponent>::deserialize(Reader &reader, RotationComponent &value)
{
    reader.read_primary("Rotation", value.rotation);
    return true;
}
