#include "pch.hpp"
#include "FontResource.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Bool Minty::Serializer<FontResource>::serialize(Writer &writer, FontResource const &value)
{
    return Bool();
}

Bool Minty::Serializer<FontResource>::deserialize(Reader &reader, FontResource &value)
{
    // Get values to deserialize
    String name = value.name;
    Vector<FontVariant> variantList;
    Map<WUInt, FontVariant> variants;

    // Deserialize values
    if (!reader.read_primary("Name", name))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Name");
        return false;
    }

    if (!reader.read_primary("Variants", variantList))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Variants");
        return false;
    }

    for (FontVariant const &variant : variantList)
    {
        WUInt const key = static_cast<WUInt>(variant.size);
        if (variants.contains(key))
        {
            variants.at(key) = variant;
        }
        else
        {
            variants.add(key, variant);
        }
    }

    // Set deserialized values
    value.name = std::move(name);
    value.variants = std::move(variants);

    return true;
}