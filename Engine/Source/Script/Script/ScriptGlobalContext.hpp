#pragma once

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief Represents the global context for scripts, providing shared data and state accessible to all script instances.
     */
    struct ScriptGlobalContext
    {
        // Time
        Float frameDeltaTime;
        Float fixedDeltaTime;
        Float totalTime;
    };
}