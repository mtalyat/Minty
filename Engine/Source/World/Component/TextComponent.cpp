#include "pch.hpp"
#include "TextComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<TextComponent>::serialize(Writer &writer, TextComponent const &value)
{
    return Bool();
}

Bool Minty::Serializer<TextComponent>::deserialize(Reader &reader, TextComponent &value)
{
    // Get values to deserialize
    String text = value.text;
    Color color = value.color;
    FontResourceHandle fontResourceHandle = value.fontResourceHandle;
    MaterialHandle materialHandle = value.materialHandle;

    // Deserialize values
    reader.read("Text", text);
    reader.read("Color", color);
    reader.read("Font", fontResourceHandle);
    reader.read("Material", materialHandle);

    // Assign deserialized values to the TextComponent object
    value.text = text;
    value.color = color;
    value.dirty = true; // Mark as dirty to ensure re-rendering
    value.fontResourceHandle = fontResourceHandle;
    value.materialHandle = materialHandle;

    return true;
}
