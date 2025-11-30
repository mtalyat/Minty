#ifndef MINTY_COMPONENT_TEXTCOMPONENT_H
#define MINTY_COMPONENT_TEXTCOMPONENT_H

/**
 * @file TextComponent.h
 * @brief Header file defining the TextComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/String.h"

namespace Minty
{
	class Font;
	class FontVariant;

	/**
	 * @brief Holds Text data for an Entity.
	 */
	struct TextComponent
		: public Component
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

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_TEXTCOMPONENT_H