#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
    /// <summary>
    /// Holds data for time elapsed over a time period recorded.
    /// </summary>
    class Stopwatch
    {
#pragma region Variables

    private:
        /// <summary>
        /// The start time in nanoseconds, when this Stopwatch was started.
        /// </summary>
        TimePoint m_start;

        /// <summary>
        /// The total amount of time in nanoseconds that have passed.
        /// </summary>
        TimeElapsed m_elapsed;

        /// <summary>
        /// Is the Stopwatch currently recording time?
        /// </summary>
        Bool m_running;

#pragma endregion

#pragma region Constructors

    public:
        /// <summary>
        /// Creates a new Stopwatch.
        /// </summary>
        Stopwatch();

#pragma endregion

#pragma region Get Set

    public:
        /// <summary>
        /// How much time has elapsed since the start?
        /// </summary>
        /// <returns>Time elapsed in nanoseconds.</returns>
        TimeElapsed get_elapsed() const;

        /// <summary>
        /// How much time (in milliseconds) have elapsed since the start?
        /// </summary>
        /// <returns></returns>
        TimeElapsed get_elapsed_ms() const;

        /// <summary>
        /// How much time (in seconds) have elapsed since the start?
        /// </summary>
        /// <returns></returns>
        float get_elapsed_s() const;

        /// <summary>
        /// How much time has elapsed since the start, as a string.
        /// </summary>
        /// <returns></returns>
        String get_elapsed_string() const;

#pragma endregion

#pragma region Methods

    public:
        /// <summary>
        /// Start recording time.
        /// </summary>
        void start();

        /// <summary>
        /// Stop recording time.
        /// </summary>
        void stop();

        /// <summary>
        /// Reset the time recorded (elapsed time to zero).
        /// </summary>
        void reset();

        /// <summary>
        /// Checks if this Stopwatch is recording time.
        /// </summary>
        /// <returns></returns>
        constexpr Bool is_running() const { return m_running; }

        /// <summary>
        /// Attempts to lap. Returns the number of laps that have occured.
        /// </summary>
        /// <param name="mod"></param>
        /// <returns>The maximum number of laps.</returns>
        TimeElapsed lap(TimeElapsed const mod);

        /// <summary>
        /// Stop, reset and start.
        /// </summary>
        inline void restart() { stop(); reset(); start(); }

#pragma endregion

#pragma region Statics

    public:
        /// <summary>
        /// Creates a new Stopwatch, and starts it immediately after.
        /// </summary>
        /// <returns></returns>
        static Stopwatch start_new() { Stopwatch watch; watch.start(); return std::move(watch); }

#pragma endregion
    };
}