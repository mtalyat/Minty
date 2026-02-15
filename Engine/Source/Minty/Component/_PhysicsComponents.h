#ifndef MINTY_COMPONENT_PHYSICSCOMPONENTS_H
#define MINTY_COMPONENT_PHYSICSCOMPONENTS_H

/**
 * @file Internal_PhysicsComponent.h
 * @brief Header file defining internal physics components.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Used to tag objects that should be controlled by the physics simulation.
     */
    struct SimulateTag
        : public Component
    {
    };

    /**
     * @brief Holds physics-related data for an Entity, from the previous fixed update.
     * Used to lerp between physics updates.
     */
    struct PhysicsComponent
        : public Component
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

#endif // MINTY_COMPONENT_PHYSICSCOMPONENTS_H