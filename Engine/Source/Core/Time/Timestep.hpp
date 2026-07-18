#pragma once

/**
 * @file Timestep.h
 * @brief Defines the Timestep class for managing time steps in the engine.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @class Timestep
     * @brief Represents a time step in the engine, used for frame updates and timing.
     */
    struct Timestep
    {
        Float deltaTime;
        Float totalTime;
    };
}