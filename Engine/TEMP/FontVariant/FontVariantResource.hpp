#pragma once

/**
 * @file FontVariant.hpp
 * @brief Header file defining the FontVariant class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Resource/Font/FontChar.h"
#include "Resource/Font/FontFlags.h"
#include "Resource/Type/Handle.h"

namespace Minty
{
	struct FontVariantInfo;

	/**
	 * @brief Represents a variant of a font, such as a specific size or style.
	 */
	class FontVariantResource
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a FontVariant with the given arguments.
		 * @param info The arguments.
		 */
		FontVariantResource(FontVariantInfo const &info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of this FontVariant.
		 * @return The size.
		 */
		inline UInt get_size() const { return m_size; }

		/**
		 * @brief Gets the flags applied to this FontVariant.
		 * @return The flags.
		 */
		inline FontFlags get_flags() const { return m_flags; }

		/**
		 * @brief Gets the height of each line in this FontVariant.
		 * @return The line height.
		 */
		inline Float get_line_height() const { return m_lineHeight; }

		/**
		 * @brief Gets the Texture this FontVariant uses to render characters.
		 * @return The texture.
		 */
		inline TextureResourceHandle const get_texture() const { return m_texture; }

		/**
		 * @brief Gets the character data for this FontVariant.
		 * @param ch The character to get the data for.
		 * @return A pointer to the FontChar data if it exists, otherwise nullptr.
		 */
		FontChar const *get_char(Char const ch) const;

		/**
		 * @brief Gets the kerning value for the given pair of characters.
		 * The kerning value is the offset of the second character relative to the first character.
		 * @param left The character on the left.
		 * @param right The character on the right.
		 * @return The kerning value.
		 */
		Float get_kerning(Char const left, Char const right) const;
		
	private:
		// packs the kerning combination into an Int
		inline static Int compact_kerning(Int const left, Int const right)
		{
			return ((left & 0xffff) << 16) | (right & 0xffff);
		}

#pragma endregion

#pragma region Variables

	private:
		UInt m_size;
		FontFlags m_flags;
		Float m_lineHeight;
		TextureResourceHandle m_texture;
		Map<Char, FontChar> m_characters;
		Map<Int, Float> m_kernings;

#pragma endregion
	};
}
