#ifndef MINTY_ASSET_GENERICASSETINFO_H
#define MINTY_ASSET_GENERICASSETINFO_H

/**
 * @file GenericAssetInfo.h
 * @brief Header file defining the GenericAssetInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/**
	 * @brief Arguments for creating a GenericAsset.
	 */
	struct GenericAssetInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = {};

		/**
		 * @brief The byte data.
		 */
		ConstantContainer data = {};
	};
}

#endif // MINTY_ASSET_GENERICASSETINFO_H