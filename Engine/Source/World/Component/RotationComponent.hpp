#pragma once

/**
 * @file RotationComponent.h
 * @brief Header file defining the RotationComponent class.
 * @author Mitchell Talyat
 */

#include "Core/Math/Quaternion.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    /**
     * @brief Component that stores the rotation of an entity in 3D space.
     */
    struct RotationComponent    
	{
        /**
         * @brief The rotation of the entity.
         */
        Quaternion rotation = Math::identity<Quaternion>();
    };

    template<>
    struct Serializer<RotationComponent>
    {
        static Bool serialize(Writer& writer, RotationComponent const& value);
        static Bool deserialize(Reader& reader, RotationComponent& value);
    };
}
