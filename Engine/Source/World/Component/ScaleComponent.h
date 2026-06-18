#pragma once

/**
 * @file ScaleComponent.h
 * @brief Header file defining the ScaleComponent class.
 * @author Mitchell Talyat
 */

#include "Core/Math/Math.h"
#include "Core/Serialize/Serializer.h"

namespace Minty
{
    /**
     * @brief Component that stores the scale of an entity in 3D space.
     */
    struct ScaleComponent    
	{
        /**
         * @brief The scale of the entity.
         */
        Float3 scale = Math::ONE;
    };

    template<>
    struct Serializer<ScaleComponent>
    {
        static Bool serialize(Writer& writer, ScaleComponent const& value);
        static Bool deserialize(Reader& reader, ScaleComponent& value);
    };
}
