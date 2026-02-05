#ifndef MINTY_ASSET_ASSETMANAGERINFO_H
#define MINTY_ASSET_ASSETMANAGERINFO_H

/**
 * @file AssetManagerInfo.h
 * @brief Header file for the AssetManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Data/Path.h"

namespace Minty
{
    /**
     * @brief Configuration information for creating an AssetManager.
     */
    struct AssetManagerInfo
    {
        /**
         * @brief A list of wrap files to load assets from.
         */
        Vector<Path> wraps = {};

#ifdef MINTY_DEBUG

        /**
         * @brief If true, the AssetManager will save the paths of the Assets.
         */
        Bool savePaths = true;

#else

        /**
         * @brief If true, the AssetManager will save the paths of the Assets.
         */
        Bool savePaths = false;

#endif
    };
}

#endif // MINTY_ASSET_ASSETMANAGERINFO_H