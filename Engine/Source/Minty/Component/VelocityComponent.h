#ifndef MINTY_COMPONENT_VELOCITYCOMPONENT_H
#define MINTY_COMPONENT_VELOCITYCOMPONENT_H

/**
 * @file VelocityComponent.h
 * @brief Header file defining the VelocityComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the velocity of an entity in 3D space.
     */
    struct VelocityComponent
        : public Component
    {
        /**
         * @brief The velocity of the entity.
         */
        Float3 velocity = Math::ZERO;
    };

    template<>
    struct Serializer<VelocityComponent>
    {
        static void serialize(Writer& writer, VelocityComponent const& value);
        static Bool deserialize(Reader& reader, VelocityComponent& value);
    };
}

#endif // MINTY_COMPONENT_VELOCITYCOMPONENT_H