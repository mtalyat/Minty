#include "pch.hpp"
#include "SpriteLayoutGroup.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<SpriteLayoutGroup>::serialize(Writer &writer, SpriteLayoutGroup const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<SpriteLayoutGroup>::deserialize(Reader &reader, SpriteLayoutGroup &value)
{
    reader.read("Offset", value.offset);
    reader.read("Size", value.count);
    reader.read("Layout", value.layout);
    return true;
}
