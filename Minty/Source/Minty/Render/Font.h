#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/FontFlags.h"

namespace Minty
{
	class FontVariant;

	/// <summary>
	/// The arguments for a font.
	/// </summary>
	struct FontBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The name of this Font.
		/// </summary>
		String name;
	};

	/// <summary>
	/// Represents a basic font that can be used to render text.
	/// </summary>
	class Font
		: public Asset
	{
#pragma region Classes

	private:
		using ID = ULong;

#pragma endregion


#pragma region Variables

	private:
		String m_name;
		Map<ID, Ref<FontVariant>> m_variants;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a Font with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Font(FontBuilder const& builder)
			: Asset(builder.id)
			, m_name(builder.name)
			, m_variants()
		{
		}

#pragma endregion

#pragma region Get Set

		/// <summary>
		/// Gets the name of this Font.
		/// </summary>
		/// <returns></returns>
		inline String const& get_name() const { return m_name; }

#pragma endregion

#pragma region Methods

		/// <summary>
		/// Adds a variant to this Font.
		/// </summary>
		/// <param name="variant">The variant to add.</param>
		void add(Ref<FontVariant> const& variant);

		/// <summary>
		/// Gets the variant for the given size and flags.
		/// </summary>
		/// <param name="size">The size of the Font.</param>
		/// <param name="flags">The flags of the Font.</param>
		/// <returns>The FontVariant.</returns>
		Ref<FontVariant> const& at(UInt const size, FontFlags const flags = FontFlags::None) const;

		/// <summary>
		/// Attempts to get the variant for the given size and flags. If no variant is found, nullptr is returned.
		/// </summary>
		/// <param name="size">The size of the Font.</param>
		/// <param name="flags">The flags of the Font.</param>
		/// <returns>The FontVariant, or nullptr if no FontVariant found.</returns>
		Ref<FontVariant> get(UInt const size, FontFlags const flags = FontFlags::None) const;

		/// <summary>
		/// Gets all of the variants for this Font.
		/// </summary>
		/// <returns>The FontVariants in a Vector.</returns>
		Vector<Ref<FontVariant>> get_variants() const;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Font.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Font; }

#pragma endregion

#pragma region Statics

	private:
		static ID create_font_id(UInt const size, FontFlags const flags)
		{
			return size | (static_cast<ID>(flags) << (sizeof(UInt) * 8));
		}

	public:
		static Owner<Font> create(FontBuilder const& builder);

#pragma endregion
	};
}