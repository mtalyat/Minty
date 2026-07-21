#pragma once

/**
 * @file Internal_PhysicsComponent.hpp
 * @brief Header file defining internal physics components.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Used to tag objects that have been registered to the physics simulation.
     */
    struct PhysicsRegisteredTag    
	{
    };

    /**
     * @brief Used to tag objects that should be controlled by the physics simulation.
     */
    struct PhysicsSimulationTag    
	{
    };

    /**
     * @brief Holds dynamic physics-related data for an Entity, from the previous fixed update.
     * Used to lerp between physics updates.
     */
    struct PhysicsComponent    
	{
        /**
         * @brief The previous position of the entity.
         */
        Float3 previousGlobalPosition = Math::ZERO;

        /**
         * @brief The previous rotation of the entity.
         */
        Quaternion previousGlobalRotation = Math::identity<Quaternion>();

        /**
         * @brief The previous position of the entity.
         */
        Float3 previousLocalPosition = Math::ZERO;

        /**
         * @brief The previous rotation of the entity.
         */
        Quaternion previousLocalRotation = Math::identity<Quaternion>();

        /**
         * @brief The previous velocity of the entity.
         */
        Float3 previousVelocity = Math::ZERO;
    };
}
