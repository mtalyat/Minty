#include "RotationComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::RotationComponent::serialize(Writer &writer) const
{
    writer.write("Rotation", rotation);
}

Bool Minty::RotationComponent::deserialize(Reader &reader)
{
    if(!reader.read_default(rotation))
    {
        reader.read("Rotation", rotation);
    }
    return true;
}
