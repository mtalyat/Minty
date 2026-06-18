#ifndef MINTY_PHYSICS_PHYSICSMATERIALINFO_H
#define MINTY_PHYSICS_PHYSICSMATERIALINFO_H

/**
 * @file PhysicsMaterialInfo.h
 * @brief Header file defining the PhysicsMaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Combine.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    struct PhysicsMaterialInfo
    {
        /**
         * @brief The UUID of the physics material. This is used to identify the material and should be unique.
         */
        UUID id = {};

        /**
         * @brief The static friction of the material.
         * Expected to be greater than or equal to the dynamic friction, otherwise the physics simulation may not work correctly.
         */
        Float staticFriction = DEFAULT_PHYSICS_FRICTION;

        /**
         * @brief The dynamic friction of the material.
         * Expected to be in the range [0, 1], where 0 is frictionless and 1 is completely rough.
         */
        Float dynamicFriction = DEFAULT_PHYSICS_FRICTION;

        /**
         * @brief The bounciness of the material. 
         * Expected to be in the range [0, 1], where 0 is not bouncy at all and 1 is perfectly bouncy.
         */
        Float bounce = DEFAULT_PHYSICS_BOUNCE;

        // /**
        //  * @brief The combine mode for friction when this material interacts with another material.
        //  */
        // Combine frictionCombine = Combine::Average;

        // /**
        //  * @brief The combine mode for bounce when this material interacts with another material.
        //  */
        // Combine bounceCombine = Combine::Average;
    };
}

#endif // MINTY_PHYSICS_PHYSICSMATERIALINFO_H