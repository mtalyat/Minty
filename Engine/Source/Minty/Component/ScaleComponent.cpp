#include "ScaleComponent.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

void Minty::ScaleComponent::serialize(Writer &writer) const
{
    writer.write("Scale", scale);
}

Bool Minty::ScaleComponent::deserialize(Reader &reader)
{
    if(!reader.read_default(scale))
    {
        reader.read("Scale", scale);
    }
    return true;
}
