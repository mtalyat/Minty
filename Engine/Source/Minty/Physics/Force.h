#ifndef MINTY_PHYSICS_FORCE_H
#define MINTY_PHYSICS_FORCE_H

/**
 * @file Force.h
 * @brief Header file defining the Force struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief The type of force to apply to a RigidBody.
     */
    enum class Force
    {
        /**
         * @brief No force applied.
         */
        None = 0,

        /**
         * @brief Force applied continuously over time.
         */
        Continuous = 1,

        /**
         * @brief Force applied instantaneously.
         */
        Impulse = 2
    };
}

#endif // MINTY_PHYSICS_FORCE_H