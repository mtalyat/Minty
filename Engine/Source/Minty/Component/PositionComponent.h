#ifndef MINTY_COMPONENT_POSITIONCOMPONENT_H
#define MINTY_COMPONENT_POSITIONCOMPONENT_H

/**
 * @file PositionComponent.h
 * @brief Header file defining the PositionComponent class.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Math.h"

namespace Minty
{
    /**
     * @brief Component that stores the position of an entity in 3D space.
     */
    struct PositionComponent
        : public Component
    {
        /**
         * @brief The position of the entity.
         */
        Float3 position = Math::ZERO;
        
		void serialize(Writer& writer) const override;
	    Bool deserialize(Reader& reader) override;
    };
}

#endif // MINTY_COMPONENT_POSITIONCOMPONENT_H