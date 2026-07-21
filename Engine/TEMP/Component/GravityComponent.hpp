#pragma once

/**
 * @file GravityComponent.hpp
 * @brief Header file defining the GravityComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the gravity scale applied to an entity.
     */
    struct GravityComponent    
	{
        /**
         * @brief The gravity vector applied to the entity.
         */
        Float scale = 1.0f;
    };

    template<>
    struct Serializer<GravityComponent>
    {
        static Bool serialize(Writer& writer, GravityComponent const& value);
        static Bool deserialize(Reader& reader, GravityComponent& value);
    };
}
