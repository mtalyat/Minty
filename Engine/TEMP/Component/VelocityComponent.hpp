#pragma once

/**
 * @file VelocityComponent.h
 * @brief Header file defining the VelocityComponent class.
 * @author Mitchell Talyat
 */

#include "Core/Math/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the velocity of an entity in 3D space.
     */
    struct VelocityComponent    
	{
        /**
         * @brief The velocity of the entity.
         */
        Float3 velocity = Math::ZERO;
    };

    template<>
    struct Serializer<VelocityComponent>
    {
        static Bool serialize(Writer& writer, VelocityComponent const& value);
        static Bool deserialize(Reader& reader, VelocityComponent& value);
    };
}
