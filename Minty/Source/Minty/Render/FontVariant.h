#pragma once
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

	/// <summary>
	/// The arguments for a FontVariant. 
	/// </summary>
	struct FontVariantBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The size of this FontVariant.
		/// </summary>
		UInt size;

		/// <summary>
		/// The flags applied to this FontVariant.
		/// </summary>
		FontFlags flags = FontFlags::None;

		/// <summary>
		/// The height of each line 
		/// </summary>
		Float lineHeight = 0.0f;

		/// <summary>
		/// The texture this FontVariant uses to render characters.
		/// </summary>
		Ref<Texture> texture = nullptr;

		/// <summary>
		/// The data for each character that this FontVariant uses.
		/// </summary>
		Vector<FontChar> characters;

		/// <summary>
		/// The list of kernings for this FontVariant. 
		/// Kernings are the adjustments made to the spacing between specific pairs of characters.
		/// </summary>
		Vector<Tuple<Char, Char, Float>> kernings;
	};

	/// <summary>
	/// Represents a variant of a font, such as a specific size or style.
	/// </summary>
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
		/// <summary>
		/// Creates a FontVariant with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		FontVariant(FontVariantBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of this FontVariant.
		/// </summary>
		/// <returns></returns>
		inline UInt get_size() const { return m_size; }

		/// <summary>
		/// Gets the flags applied to this FontVariant.
		/// </summary>
		/// <returns></returns>
		inline FontFlags get_flags() const { return m_flags; }

		/// <summary>
		/// Gets the height of each line in this FontVariant.
		/// </summary>
		/// <returns></returns>
		inline Float get_line_height() const { return m_lineHeight; }

		/// <summary>
		/// Gets the Texture this FontVariant uses to render characters.
		/// </summary>
		/// <returns></returns>
		inline Ref<Texture> const& get_texture() const { return m_texture; }

		/// <summary>
		/// Gets the Material this FontVariant uses for rendering.
		/// </summary>
		/// <returns></returns>
		inline Ref<Material> const& get_material() const { return m_material; }

		/// <summary>
		/// Gets the character data for this FontVariant.
		/// </summary>
		/// <param name="ch">The character to get the data for.</param>
		/// <returns>A pointer to the FontChar data if it exists, otherwise nullptr.</returns>
		FontChar const* get_char(Char const ch) const;

		/// <summary>
		/// Gets the kerning value for the given pair of characters.
		/// The kerning value is the offset of the second character relative to the first character.
		/// </summary>
		/// <param name="left">The character on the left.</param>
		/// <param name="right">The character on the right.</param>
		/// <returns>The kerning value.</returns>
		Float get_kerning(Char const left, Char const right) const;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>FontVariant.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::FontVariant; }

#pragma endregion

#pragma region Statics

	private:
		// packs the kerning combination into an Int
		static Int compact_kerning(Int const left, Int const right)
		{
			return ((left & 0xffff) << 16) | (right & 0xffff);
		}

	public:
		/// <summary>
		/// Creates a FontVariant with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A FontVariant Owner.</returns>
		static Owner<FontVariant> create(FontVariantBuilder const& builder = {});

#pragma endregion
};
}