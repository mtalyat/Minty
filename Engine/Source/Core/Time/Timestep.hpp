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
    class Timestep
    {
#pragma region Constructors

    public:
        /**
         * @brief Constructs a new Timestep with the given delta and total time.
         * @param delta The delta time for this timestep.
         * @param total The total time since the start.
         */
        explicit Timestep(Float const elapsed, Float const total)
            : m_elapsed(elapsed)
            , m_total(total)
        {
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the delta time of the timestep.
         * @return The delta time as a Float.
         */
        inline Float get_elapsed() const { return m_elapsed; }

        /**
         * @brief Gets the total time of the timestep.
         * @return The total time as a Float.
         */
        inline Float get_total() const { return m_total; }

#pragma endregion

#pragma region Variables

    public:
        Float m_elapsed;
        Float m_total;

#pragma endregion
    };
}