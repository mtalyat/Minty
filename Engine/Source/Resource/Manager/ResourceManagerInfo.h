#pragma once

/**
 * @file ResourceManagerInfo.h
 * @brief Header file defining the ResourceManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/Path.h"
#include "Core/Data/Vector.h"

namespace Minty
{
    /**
     * @brief Configuration information for creating an ResourceManager.
     */
    struct ResourceManagerInfo
    {
        /**
         * @brief A list of wrap files to load assets from.
         */
        Vector<Path> wraps = {};
    };
}