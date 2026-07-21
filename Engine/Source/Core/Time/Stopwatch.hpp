#pragma once

/**
 * @file Stopwatch.hpp
 * @brief Header file defining the Stopwatch class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/String.hpp"

namespace Minty
{
    /**
     * @brief Holds data for time elapsed over a time period recorded.
     */
    class Stopwatch
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a new Stopwatch.
         */
        Stopwatch();

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief How much time has elapsed since the start?
         * @return Time elapsed in nanoseconds.
         */
        TimePoint get_elapsed() const;

        /**
         * @brief How much time (in seconds) have elapsed since the start?
         * @return
         */
        Float get_elapsed_s() const;

        /**
         * @brief How much time has elapsed since the start, as a string.
         * @return
         */
        String get_elapsed_string() const;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Start recording time.
         */
        void start();

        /**
         * @brief Stop recording time.
         */
        void stop();

        /**
         * @brief Reset the time recorded (elapsed time to zero).
         */
        void reset();

        /**
         * @brief Checks if this Stopwatch is recording time.
         * @return
         */
        inline Bool is_running() const { return m_running; }

        /**
         * @brief Attempts to lap. Returns the number of laps that have occured.
         * 
	 * Ex. If the time elapsed is 10 seconds, and the mod is 3 seconds, the result will be 3, while setting the new elapsed time to 1.
         * @param mod The lap length in TimePoint.
         * @return The maximum number of laps.
         */
        Size lap(TimePoint const mod);

        /**
         * @brief Stop, reset and start.
         */
        inline void restart() { stop(); reset(); start(); }

        /**
         * @brief Creates a new Stopwatch, and starts it immediately after.
         * @return
         */
        static Stopwatch start_new() { Stopwatch watch; watch.start(); return std::move(watch); }

#pragma endregion

#pragma region Variables

    private:
        TimePoint m_start;
        TimePoint m_elapsed;
        Bool m_running;

#pragma endregion
    };
}