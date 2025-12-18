#ifndef MINTY_COMPONENT_SCALECOMPONENT_H
#define MINTY_COMPONENT_SCALECOMPONENT_H

/**
 * @file ScaleComponent.h
 * @brief Header file defining the ScaleComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the scale of an entity in 3D space.
     */
    struct ScaleComponent
        : public Component
    {
        /**
         * @brief The scale of the entity.
         */
        Float3 scale = Math::ONE;
        
        void serialize(Writer& writer) const override;
        Bool deserialize(Reader& reader) override;
    };
}

#endif // MINTY_COMPONENT_SCALECOMPONENT_H