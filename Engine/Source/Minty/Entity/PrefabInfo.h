#ifndef MINTY_ENTITY_PREFABINFO_H
#define MINTY_ENTITY_PREFABINFO_H

/**
 * @file PrefabInfo.h
 * @brief Header file defining the PrefabInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/UUID.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/ConstantContainer.h"

namespace Minty
{
    /**
     * @brief Information required to create a Prefab.
     */
    struct PrefabInfo
    {
        /**
         * @brief The unique identifier for the Prefab.
         */
        UUID id = {};

        /**
         * @brief The source data for the Prefab.
         */
        Shared<ConstantContainer> source = nullptr;
    };
}

#endif // MINTY_ENTITY_PREFABINFO_H