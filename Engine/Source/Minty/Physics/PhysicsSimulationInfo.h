#ifndef MINTY_PHYSICS_PHYSICSSIMULATIONINFO_H
#define MINTY_PHYSICS_PHYSICSSIMULATIONINFO_H

/**
 * @file PhysicsSimulationInfo.h
 * @brief Header file defining the PhysicsSimulationInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief The arguments to create a PhysicsSimulation.
     */
    struct PhysicsSimulationInfo
    {
        /**
         * @brief The gravity vector applied to all objects in the simulation.
         */
        Float3 gravity = Float3(0.0f, DEFAULT_PHYSICS_GRAVITY, 0.0f);
    };
}

#endif // MINTY_PHYSICS_PHYSICSSIMULATIONINFO_H