#ifndef MINTY_COMPONENT_ROTATIONCOMPONENT_H
#define MINTY_COMPONENT_ROTATIONCOMPONENT_H

/**
 * @file RotationComponent.h
 * @brief Header file defining the RotationComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the rotation of an entity in 3D space.
     */
    struct RotationComponent
        : public Component
    {
        /**
         * @brief The rotation of the entity.
         */
        Quaternion rotation = Math::identity<Quaternion>();
        
        void serialize(Writer& writer) const override;
        Bool deserialize(Reader& reader) override;
    };
}

#endif // MINTY_COMPONENT_ROTATIONCOMPONENT_H