#include "VelocityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::VelocityComponent::serialize(Writer &writer) const
{
    writer.write("Velocity", velocity);
}

Bool Minty::VelocityComponent::deserialize(Reader &reader)
{
    if(!reader.read_default(velocity))
    {
        reader.read("Velocity", velocity);
    }
    return true;
}
