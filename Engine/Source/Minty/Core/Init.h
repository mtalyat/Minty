#ifndef MINTY_CORE_INIT_H
#define MINTY_CORE_INIT_H

/**
 * @file Init.h
 * @brief Header file for initializing the Minty engine.
 * @author Mitchell Talyat
 */

#include "Minty/Debug/DebugFlags.h"

namespace Minty
{
    /**
     * @brief Struct containing information for initializing the Minty engine.
     */
    struct MintyInfo
    {
        /**
         * @brief The debug flags to initialize with.
         */
        DebugFlags debugFlags = DebugFlags::Default;
    };

    /**
     * @brief Initializes the Minty engine.
     * @param info The information to initialize with.
     */
    void initialize(MintyInfo const &info = {});

    /**
     * @brief Disposes of the Minty engine, cleaning up resources.
     */
    void dispose();
}

#endif // MINTY_CORE_INIT_H