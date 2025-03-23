#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// Arguments for creating a GenericAsset.
	/// </summary>
	struct GenericAssetBuilder
	{
		UUID id = INVALID_ID;
		ConstantContainer data = {};
	};

	/// <summary>
	/// A generic Asset.
	/// </summary>
	class GenericAsset
		: public Asset
	{
#pragma region Variables

	private:
		ConstantContainer m_data;

#pragma endregion

#pragma region Constructors

	public:
		GenericAsset(GenericAssetBuilder const& builder)
			: Asset(builder.id)
			, m_data(builder.data)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the data of this Asset.
		/// </summary>
		/// <returns>The ConstantContainer with the data for this Asset.</returns>
		ConstantContainer& get_data() { return m_data; }

		/// <summary>
		/// Gets the data of this Asset.
		/// </summary>
		/// <returns>The ConstantContainer with the data for this Asset.</returns>
		ConstantContainer const& get_data() const { return m_data; }

		/// <summary>
		/// Gets the data of this Asset as a String.
		/// </summary>
		/// <returns>A String of the data.</returns>
		String get_text() const;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>The AssetType.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Generic; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new GenericAsset.
		/// </summary>
		/// <param name="builder">The builder.</param>
		/// <returns>A GenericAsset Owner.</returns>
		static Owner<GenericAsset> create(GenericAssetBuilder const& builder = {});

#pragma endregion

	};
}