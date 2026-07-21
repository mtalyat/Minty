#pragma once

/**
 * @file PositionComponent.hpp
 * @brief Header file defining the PositionComponent class.
 * @author Mitchell Talyat
 */

#include "Core/Math/Math.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    /**
     * @brief Component that stores the position of an entity in 3D space.
     */
    struct PositionComponent    
	{
        /**
         * @brief The position of the entity.
         */
        Float3 position = Math::ZERO;
    };

    template<>
    struct Serializer<PositionComponent>
    {
        static Bool serialize(Writer& writer, PositionComponent const& value);
        static Bool deserialize(Reader& reader, PositionComponent& value);
    };
}
