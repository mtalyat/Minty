#include "PositionComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::PositionComponent::serialize(Writer &writer) const
{
    writer.write("Position", position);
}

Bool Minty::PositionComponent::deserialize(Reader &reader)
{
    if(!reader.read_default(position))
    {
        reader.read("Position", position);
    }
    return true;
}
