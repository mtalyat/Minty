#ifndef MINTY_RENDER_FONTVARIANT_H
#define MINTY_RENDER_FONTVARIANT_H

/**
 * @file FontVariant.h
 * @brief Header file defining the FontVariant class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/FontChar.h"
#include "Minty/Render/FontFlags.h"

namespace Minty
{
	class Texture;
	class Material;
	struct FontVariantInfo;

	/**
	 * @brief Represents a variant of a font, such as a specific size or style.
	 */
	class FontVariant
		: public Asset
	{
#pragma region Variables

	private:
		UInt m_size;
		FontFlags m_flags;
		Float m_lineHeight;
		Ref<Texture> m_texture;
		Ref<Material> m_material;
		Map<Char, FontChar> m_characters;
		Map<Int, Float> m_kernings;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a FontVariant with the given arguments.
		 * @param info The arguments.
		 */
		FontVariant(FontVariantInfo const &info);

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
		inline Ref<Texture> const &get_texture() const { return m_texture; }

		/**
		 * @brief Gets the Material this FontVariant uses for rendering.
		 * @return The material.
		 */
		inline Ref<Material> const &get_material() const { return m_material; }

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

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return FontVariant.
		 */
		inline AssetType get_asset_type() const override { return AssetType::FontVariant; }

#pragma endregion

#pragma region Statics

	private:
		// packs the kerning combination into an Int
		static Int compact_kerning(Int const left, Int const right)
		{
			return ((left & 0xffff) << 16) | (right & 0xffff);
		}

	public:
		/**
		 * @brief Creates a FontVariant with the given arguments.
		 * @param info The arguments.
		 * @return A FontVariant Owner.
		 */
		static Shared<FontVariant> create(FontVariantInfo const &info);

		/**
		 * @brief Creates a default FontVariant.
		 * @return A FontVariant Owner.
		 */
		static Shared<FontVariant> create();

#pragma endregion
	};
}

#endif // MINTY_RENDER_FONTVARIANT_H