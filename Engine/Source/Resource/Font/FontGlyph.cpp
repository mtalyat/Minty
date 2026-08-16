#include "pch.hpp"
#include "FontGlyph.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<FontGlyph>::serialize(Writer &writer, FontGlyph const &value)
{
    return Bool();
}

Bool Minty::Serializer<FontGlyph>::deserialize(Reader &reader, FontGlyph &value)
{
    // Get values to deserialize
    Char id = value.id;
    Float2 position = value.position;
    Float2 size = value.size;
    Float2 offset = value.offset;
    Float advance = value.advance;
    Int page = value.page;

    // Deserialize values
    if(!reader.read_primary("ID", id))
    {
        // Some font assets encode space as a list item with no explicit ID.
        id = ' ';
    }

    // Blank inline IDs can surface as line breaks; normalize them to a space glyph.
    if (id == '\n' || id == '\r' || id == '\0')
    {
        id = ' ';
    }

    reader.read("Position", position);
    reader.read("Size", size);
    reader.read("Offset", offset);
    reader.read("Advance", advance);
    reader.read("Page", page);

    // Assign deserialized values to the FontGlyph object
    value.id = id;
    value.position = position;
    value.size = size;
    value.offset = offset;
    value.advance = advance;
    value.page = page;

    return true;
}
