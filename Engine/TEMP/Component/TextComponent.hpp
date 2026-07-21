#pragma once

/**
 * @file TextComponent.hpp
 * @brief Header file defining the TextComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/String.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"

namespace Minty
{
	/**
	 * @brief Holds Text data for an Entity.
	 */
	struct TextComponent	
	{
		/**
		 * @brief The text to render.
		 */
		String text = "";

		/**
		 * @brief The color of the text.
		 */
		Color color = Color::white();

		/**
		 * @brief The font to render the text in.
		 */
		Ref<Font> font = nullptr;

		/**
		 * @brief The specific variant of the font to render the text in.
		 */
		Ref<FontVariant> fontVariant = nullptr;
	};

	template<>
	struct Serializer<TextComponent>
	{
		static Bool serialize(Writer& writer, TextComponent const& value);
		static Bool deserialize(Reader& reader, TextComponent& value);
	};
}
