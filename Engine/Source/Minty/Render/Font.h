#ifndef MINTY_RENDER_FONT_H
#define MINTY_RENDER_FONT_H

/**
 * @file Font.h
 * @brief Header file defining the Font class and FontInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/FontFlags.h"

namespace Minty
{
	class FontVariant;
	struct FontInfo;

	/**
	 * @brief Represents a basic font that can be used to render text.
	 */
	class Font
		: public Asset
	{
#pragma region Types

	private:
		using ID = ULong;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a Font with the given arguments.
		 * @param info The arguments.
		 */
		Font(FontInfo const& info);

#pragma endregion

#pragma region Accessors

		/**
		 * @brief Gets the name of this Font.
		 * @return The name.
		 */
		inline String const& get_name() const { return m_name; }

#pragma endregion

#pragma region Methods

		/**
		 * @brief Gets the variant for the given size and flags.
		 * @param size The size of the Font.
		 * @param flags The flags of the Font.
		 * @return The FontVariant.
		 */
		Ref<FontVariant> const& at(UInt const size, FontFlags const flags = FontFlags::None) const;

		/**
		 * @brief Attempts to get the variant for the given size and flags. If no variant is found, nullptr is returned.
		 * @param size The size of the Font.
		 * @param flags The flags of the Font.
		 * @return The FontVariant, or nullptr if no FontVariant found.
		 */
		Ref<FontVariant> get(UInt const size, FontFlags const flags = FontFlags::None) const;

		/**
		 * @brief Gets all of the variants for this Font.
		 * @return The FontVariants in a Vector.
		 */
		Vector<Ref<FontVariant>> get_variants() const;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Font.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Font; }

		/**
		 * @brief Creates a Font with the given arguments.
		 * @param info The arguments.
		 * @return A Font Owner.
		 */
		static Shared<Font> create(FontInfo const& info);

		/**
		 * @brief Creates a default Font.
		 * @return A Font Owner.
		 */
		static Shared<Font> create();

	private:
		static ID create_font_id(UInt const size, FontFlags const flags)
		{
			return size | (static_cast<ID>(flags) << (sizeof(UInt) * 8));
		}

#pragma endregion

#pragma region Variables

	private:
		String m_name;
		Map<ID, Ref<FontVariant>> m_variants;

#pragma endregion
	};
}

#endif // MINTY_RENDER_FONT_H