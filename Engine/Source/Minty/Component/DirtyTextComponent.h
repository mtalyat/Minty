#ifndef MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H
#define MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H

/**
 * @file DirtyTextComponent.h
 * @brief Header file defining the DirtyTextComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
    /**
     * @brief Marks an Entity as having a dirty TextComponent.
     */
    struct DirtyTextComponent
        : public Component
    {
    };

    template<>
    struct Serializer<DirtyTextComponent>
    {
        static void serialize(Writer& writer, DirtyTextComponent const& value){}
        static void deserialize(Reader& reader, DirtyTextComponent& value){}
    };
}

#endif // MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H