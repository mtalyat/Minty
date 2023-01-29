#pragma once

#include "M_Object.h"

namespace minty
{
    /// <summary>
    /// Holds data for time elapsed over a time period recorded.
    /// </summary>
    class MINTY_API Stopwatch :
        public Object
    {
    private:
        /// <summary>
        /// The start time in clock ticks, when this Stopwatch was started.
        /// </summary>
        clock_t m_start;

        /// <summary>
        /// The total amount of time in click ticks that have passed.
        /// </summary>
        long m_elapsed;

        /// <summary>
        /// Is the Stopwatch currently recording time?
        /// </summary>
        bool m_running;

    public:
        /// <summary>
        /// Creates a new Stopwatch.
        /// </summary>
        Stopwatch();

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
        /// Stop, reset and start.
        /// </summary>
        inline void restart() { stop(); reset(); start(); }

        /// <summary>
        /// How much time has elapsed since the start?
        /// </summary>
        /// <returns></returns>
        long elapsed() const;

        /// <summary>
        /// Manually set the time elapsed from the start.
        /// </summary>
        /// <param name="elapsed"></param>
        void setElapsed(long const elapsed);

        /// <summary>
        /// Creates a new Stopwatch, and starts it immediately after.
        /// </summary>
        /// <returns></returns>
        inline static Stopwatch startNew() { Stopwatch watch; watch.start(); return watch; }

        std::string const toString() const override;
    };
}
