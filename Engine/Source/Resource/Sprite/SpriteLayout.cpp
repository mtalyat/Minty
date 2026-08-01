#include "pch.hpp"
#include "SpriteLayout.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<SpriteLayout>::serialize(Writer &writer, SpriteLayout const &value)
{
    writer.write("Mode", value.coordinateMode);
    writer.write("Offset", value.offset);
    writer.write("Size", value.size);
    writer.write("Pivot", value.pivot);
    return true;
}

Bool Minty::Serializer<SpriteLayout>::deserialize(Reader &reader, SpriteLayout &value)
{
    reader.read("Mode", value.coordinateMode);
    reader.read("Offset", value.offset);
    reader.read("Size", value.size);
    reader.read("Pivot", value.pivot);
    return true;
}
