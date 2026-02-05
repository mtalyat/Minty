#ifndef MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H
#define MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H

/**
 * @file DirtyTextTag.h
 * @brief Header file defining the DirtyTextTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
    /**
     * @brief Marks an Entity as having a dirty TextComponent.
     */
    struct DirtyTextTag
        : public Component
    {
    };
}

#endif // MINTY_COMPONENT_DIRTYTEXTCOMPONENT_H