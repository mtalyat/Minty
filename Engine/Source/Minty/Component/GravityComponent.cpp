#include "GravityComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::GravityComponent::serialize(Writer &writer) const
{
    writer.write("Scale", scale);
}

Bool Minty::GravityComponent::deserialize(Reader &reader)
{
    if(!reader.read_default(scale))
    {
        reader.read("Scale", scale);
    }

    return true;
}
