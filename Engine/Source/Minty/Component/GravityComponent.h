#ifndef MINTY_COMPONENT_GRAVITYCOMPONENT_H
#define MINTY_COMPONENT_GRAVITYCOMPONENT_H

/**
 * @file GravityComponent.h
 * @brief Header file defining the GravityComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the gravity scale applied to an entity.
     */
    struct GravityComponent
        : public Component
    {
        /**
         * @brief The gravity vector applied to the entity.
         */
        Float scale = 1.0f;
        
        void serialize(Writer& writer) const override;
        Bool deserialize(Reader& reader) override;
    };
}

#endif // MINTY_COMPONENT_GRAVITYCOMPONENT_H