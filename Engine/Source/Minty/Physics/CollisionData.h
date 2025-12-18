#ifndef MINTY_PHYSICS_COLLISIONDATA_H
#define MINTY_PHYSICS_COLLISIONDATA_H

/**
 * @file CollisionData.h
 * @brief Header file defining collision data structures.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Math.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
    struct CollisionData
    {
        Float3 point = Math::ZERO;
        Float3 normal = Math::ZERO;
        Float3 otherPoint = Math::ZERO;
        Float distance = 0.0f;
        Entity entity = INVALID_ENTITY;
        Entity otherEntity = INVALID_ENTITY;
    };
}

#endif // MINTY_PHYSICS_COLLISIONDATA_H