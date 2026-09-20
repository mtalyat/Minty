#pragma once

#include "Core/Data/Vector.hpp"
#include "Script/Type/Handle.hpp"

namespace Minty
{
    struct ScriptComponentData
    {
        ScriptHandle handle = INVALID_HANDLE;
        Bool enabled = true;
    };

    /**
     * @brief Component that holds a list of script handles attached to an entity.
     * @note One script component per entity, but multiple scripts per entity are allowed.
     */
    struct ScriptComponent
    {
        /**
         * @brief List of script handles attached to this component.
         */
        Vector<ScriptComponentData> scripts;
    };
}