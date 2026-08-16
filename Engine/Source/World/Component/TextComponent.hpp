#pragma once

#include "Core/Data/String.hpp"
#include "Render/Type/Handle.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Type/Color.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct TextComponent
    {
        // The text to render
        String text = String();

        Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        // When true, the text will be re-rendered to the geometry
        Bool dirty = true;

        // The font to use for rendering the text
        FontResourceHandle fontResourceHandle = INVALID_HANDLE;

        // The material to use for rendering glyphs.
        MaterialHandle materialHandle = INVALID_HANDLE;

        // The geometry handle for the text mesh
        GeometryHandle geometryHandle = INVALID_HANDLE;
    };

	template<>
	struct Serializer<TextComponent>
	{
		static Bool serialize(Writer& writer, TextComponent const& value);
		static Bool deserialize(Reader& reader, TextComponent& value);
	};
}
