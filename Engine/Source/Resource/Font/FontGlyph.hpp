#pragma once

/**
 * @file FontGlyph.hpp
 * @brief Header file defining the FontGlyph struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Core/Type/Float2.hpp"

namespace Minty
{
	/**
	 * @brief Holds data for a single character in a Font.
	 */
	struct FontGlyph
	{
		/**
		 * @brief The character.
		 */
		Char id;

		Float2 position;

		Float2 size;

		Float2 offset;

		/**
		 * @brief The distance to advance the cursor after rendering this character.
		 */
		Float advance;

		Int page;
	};

	template<>
	struct Serializer<FontGlyph>
	{
		static Bool serialize(Writer &writer, FontGlyph const &value);
		static Bool deserialize(Reader &reader, FontGlyph &value);
	};
}
