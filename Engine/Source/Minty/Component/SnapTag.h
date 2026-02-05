#ifndef MINTY_COMPONENT_SNAPCOMPONENT_H
#define MINTY_COMPONENT_SNAPCOMPONENT_H

/**
 * @file SnapTag.h
 * @brief Header file for the SnapTag.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
    /**
     * @struct SnapTag
     * @brief Component indicating that an entity should snap to a grid or specific positions.
     */
    struct SnapTag 
        : public Component
    {
    };

    template<>
    struct Serializer<SnapTag>
    {
        static void serialize(Writer& writer, SnapTag const& value){}
        static Bool deserialize(Reader& reader, SnapTag& value){}
    };
}

#endif // MINTY_COMPONENT_SNAPCOMPONENT_H