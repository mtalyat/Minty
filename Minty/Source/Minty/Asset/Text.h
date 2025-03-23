#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// Arguments for creating a Text Asset.
	/// </summary>
	struct TextBuilder
	{
		UUID id = INVALID_ID;
		String text = "";
	};

	/// <summary>
	/// A text file Asset.
	/// </summary>
	class Text
		: public Asset
	{
#pragma region Variables

	private:
		String m_text;

#pragma endregion

#pragma region Constructors

	public:
		Text(TextBuilder const& builder)
			: Asset(builder.id)
			, m_text(builder.text)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the text of this Asset.
		/// </summary>
		/// <returns>The text as a String.</returns>
		String const& get_text() const { return m_text; }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>The AssetType.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Text; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Text Asset.
		/// </summary>
		/// <param name="builder">The builder.</param>
		/// <returns>A Text Owner.</returns>
		static Owner<Text> create(TextBuilder const& builder = {});

#pragma endregion

	};
}