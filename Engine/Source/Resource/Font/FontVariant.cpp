#include "FontVariant.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Core/Data/UUID.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Resource/Texture/TextureResource.hpp"

using namespace Minty;

Int Minty::FontVariant::make_kerning_key(Char const first, Char const second)
{
    UInt8 const a = static_cast<UInt8>(first);
    UInt8 const b = static_cast<UInt8>(second);
    return static_cast<Int>((static_cast<UInt16>(a) << 8) | static_cast<UInt16>(b));
}

Bool Minty::Serializer<FontVariant>::serialize(Writer &writer, FontVariant const &value)
{
    return Bool();
}

Bool Minty::Serializer<FontVariant>::deserialize(Reader &reader, FontVariant &value)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();

    // Get values to deserialize
    UInt size = value.size;
    FontFlags flags = value.flags;
    Float lineHeight = value.lineHeight;
    Vector<UUID> pageIds;
    Vector<TextureResourceHandle> pages;
    Map<Char, FontGlyph> characters;
    Map<Int, Float> kernings;
    Vector<FontGlyph> glyphs;

    // Deserialize values

    // Info section required
    if (reader.indent("Info"))
    {
        if (!reader.read("Size", size))
        {
            MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Size");
            return false;
        }
        reader.read("Flags", flags);

        reader.outdent();
    }
    else
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Info");
        return false;
    }

    // Common section required
    if (reader.indent("Common"))
    {
        if (!reader.read("LineHeight", lineHeight))
        {
            MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "LineHeight");
            return false;
        }

        reader.outdent();
    }
    else
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Common");
        return false;
    }

    // Read pages
    if (!reader.read("Pages", pageIds))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Pages");
        return false;
    }

    for (UUID const &pageId : pageIds)
    {
        TextureResourceHandle pageHandle = resourceManager.find_handle<TextureResource>(pageId);
        if (!pageHandle.is_valid())
        {
            ImageResourceHandle const imageHandle = resourceManager.find_handle<ImageResource>(pageId);
            if (imageHandle.is_valid())
            {
                TextureResource texture{};
                texture.imageHandle = imageHandle;
                pageHandle = resourceManager.add<TextureResource>(std::move(texture), UUID::generate());
            }
        }

        if (!pageHandle.is_valid())
        {
            MINTY_ERROR_A(ErrorCodeEnum::Resource_MissingDependency, Parser<UUID>::to_string(pageId).get_data());
            return false;
        }

        pages.add(pageHandle);
    }

    // Must have at least one page
    if (pages.is_empty())
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Pages");
        return false;
    }

    // Read in the font characters
    if (!reader.read("Chars", glyphs))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Chars");
        return false;
    }

    for (FontGlyph const &glyph : glyphs)
    {
        if (characters.contains(glyph.id))
        {
            characters.at(glyph.id) = glyph;
        }
        else
        {
            characters.add(glyph.id, glyph);
        }
    }

    // Read in the font kernings
    if (!reader.indent("Kernings"))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Serialization_MissingKey, "Kernings");
        return false;
    }
    String pair;
    Float amount;
    while (reader.read_next(pair, amount))
    {
        // Make sure proper format is used for the kerning pair
        if (pair.get_size() != 2)
        {
            MINTY_ERROR_A(ErrorCodeEnum::Serialization_InvalidFormat, pair.get_data());
            return false;
        }
        
        // Add the kerning pair to the map
        Int const key = FontVariant::make_kerning_key(pair[0], pair[1]);
        if (kernings.contains(key))
        {
            kernings.at(key) = amount;
        }
        else
        {
            kernings.add(key, amount);
        }
    }

    reader.outdent();

    // Set the values to the resource
    value.size = size;
    value.flags = flags;
    value.lineHeight = lineHeight;
    value.pages = std::move(pages);
    value.characters = std::move(characters);
    value.kernings = std::move(kernings);

    return true;
}