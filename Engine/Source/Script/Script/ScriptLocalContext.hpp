#pragma once

#include "World/Entity/Entity.hpp"

namespace Minty
{
    /**
     * @brief Represents the local context for a script, providing access to the entity associated with the script instance.
     */
    struct ScriptLocalContext
    {
        EntityHandle entity = INVALID_ENTITY; // The entity associated with this script context, if any
    };
}