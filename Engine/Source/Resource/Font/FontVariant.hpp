#pragma once

/**
 * @file FontVariant.hpp
 * @brief Header file defining the FontVariant class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Resource/Font/FontGlyph.hpp"
#include "Resource/Font/FontFlags.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	struct FontVariant
	{
		UInt size;
		FontFlags flags;
		Float lineHeight;
		Vector<TextureResourceHandle> pages;
		Map<Char, FontGlyph> characters;
		Map<Int, Float> kernings;
	};

    template<>
    struct Serializer<FontVariant>
    {
        static Bool serialize(Writer &writer, FontVariant const &value);
        static Bool deserialize(Reader &reader, FontVariant &value);
    };
}
