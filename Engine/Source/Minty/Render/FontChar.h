#ifndef MINTY_RENDER_FONTCHAR_H
#define MINTY_RENDER_FONTCHAR_H

/**
 * @file FontChar.h
 * @brief Header file defining the FontChar struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @brief Holds data for a single character in a Font.
	 */
	struct FontChar
	{
		/**
		 * @brief The character.
		 */
		Char id;

		/**
		 * @brief The x position within the texture.
		 */
		Float x;

		/**
		 * @brief The y position within the texture.
		 */
		Float y;

		/**
		 * @brief The width of the character in the texture.
		 */
		Float width;

		/**
		 * @brief The height of the character in the texture.
		 */
		Float height;

		/**
		 * @brief The x offset to apply when rendering this character.
		 */
		Float xOffset;
		
		/**
		 * @brief The y offset to apply when rendering this character.
		 */
		Float yOffset;

		/**
		 * @brief The distance to advance the cursor after rendering this character.
		 */
		Float xAdvance;
	};
}

#endif // MINTY_RENDER_FONTCHAR_H