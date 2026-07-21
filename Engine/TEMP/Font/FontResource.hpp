#pragma once

/**
 * @file Font.hpp
 * @brief Header file defining the Font class and FontInfo struct.
 * @author Mitchell Talyat
 */

#include "FontFlags.h"
#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Serializer.h"
#include "Resource/Type/Handle.h"

namespace Minty
{
	struct FontInfo;

	/**
	 * @brief Represents a basic font that can be used to render text.
	 */
	class FontResource
	{
#pragma region Types

	private:
		using ID = WUInt;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a Font with the given arguments.
		 * @param info The arguments.
		 */
		FontResource(FontInfo const& info);

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
		FontVariantHandle at(UInt const size, FontFlags const flags = FontFlagsEnum::None) const;

		/**
		 * @brief Attempts to get the variant for the given size and flags. If no variant is found, nullptr is returned.
		 * @param size The size of the Font.
		 * @param flags The flags of the Font.
		 * @return The FontVariant, or nullptr if no FontVariant found.
		 */
		FontVariantHandle get(UInt const size, FontFlags const flags = FontFlagsEnum::None) const;

		/**
		 * @brief Gets all of the variants for this Font.
		 * @return The FontVariants in a Vector.
		 */
		Vector<FontVariantHandle> get_variants() const;

	private:
		static ID create_font_id(UInt const size, FontFlags const flags)
		{
			return size | (static_cast<ID>(flags.flags) << (sizeof(UInt) * 8));
		}

#pragma endregion

#pragma region Variables

	private:
		String m_name;
		Map<ID, FontVariantHandle> m_variants;

#pragma endregion
	};
}
