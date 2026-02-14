#ifndef MINTY_PHYSICS_RigidbodyINFO_H
#define MINTY_PHYSICS_RigidbodyINFO_H

/**
 * @file RigidbodyInfo.h
 * @brief Header file defining the RigidbodyInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/Constraints.h"

namespace Minty
{
    /**
     * @brief The arguments to create a Rigidbody.
     */
    struct RigidbodyInfo
    {
        /**
         * @brief The mass of the rigid body.
         */
        Float mass = 1.0f;

        /**
         * @brief The friction of the rigid body.
         */
        Float friction = 0.5f;

        /**
         * @brief The bounciness of the rigid body.
         */
        Float bounce = 0.0f;

        /**
         * @brief The constraints applied to the rigid body.
         */
        Constraints rotationConstraints = Constraints::None;

        /**
         * @brief The collider associated with the rigid body.
         */
        Shared<Collider> collider = nullptr;

        /**
         * @brief Whether the rigid body is kinematic.
         */
        Bool isKinematic = false;

        /**
         * @brief Whether the rigid body is static.
         */
        Bool isStatic = false;
    };
}

#endif // MINTY_PHYSICS_RigidbodyINFO_H