#ifndef MINTY_ASSET_GENERICASSET_H
#define MINTY_ASSET_GENERICASSET_H

/**
 * @file GenericAsset.h
 * @brief Header file defining the GenericAsset class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	struct GenericAssetInfo;
	
	/**
	 * @brief A generic Asset. It could be anything!
	 */
	class GenericAsset
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GenericAsset.
		 * @param info The info.
		 */
		GenericAsset(GenericAssetInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the data of this Asset.
		 * @return The ConstantContainer with the data for this Asset.
		 */
		ConstantContainer& get_data() { return m_data; }

		/**
		 * @brief Gets the data of this Asset.
		 * @return The ConstantContainer with the data for this Asset.
		 */
		ConstantContainer const& get_data() const { return m_data; }

		/**
		 * @brief Gets the data of this Asset as a String.
		 * @return A String of the data.
		 */
		String get_text() const;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return The AssetType.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Generic; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates a new GenericAsset.
		 * @param info The info.
		 * @return A GenericAsset Owner.
		 */
		static Shared<GenericAsset> create(GenericAssetInfo const& info);

		/**
		 * @brief Creates a default GenericAsset.
		 * @return A GenericAsset Owner.
		 */
		static Shared<GenericAsset> create();

#pragma endregion

#pragma region Variables

	private:
		ConstantContainer m_data;

#pragma endregion
	};
}

#endif // MINTY_ASSET_GENERICASSET_H