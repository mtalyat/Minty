#ifndef MINTY_PHYSICS_RIGIDBODYINFO_H
#define MINTY_PHYSICS_RIGIDBODYINFO_H

/**
 * @file RigidBodyInfo.h
 * @brief Header file defining the RigidBodyInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief The arguments to create a RigidBody.
     */
    struct RigidBodyInfo
    {
        /**
         * @brief Whether the rigid body is kinematic.
         */
        Bool isKinematic = false;

        /**
         * @brief The mass of the rigid body.
         */
        Float mass = 1.0f;
    };
}

#endif // MINTY_PHYSICS_RIGIDBODYINFO_H