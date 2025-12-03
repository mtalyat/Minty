#ifndef MINTY_TIME_TIMECONTROLLER_H
#define MINTY_TIME_TIMECONTROLLER_H

/**
 * @file TimeController.h
 * @brief Header file defining the TimeController class and TimeControllerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Time/Time.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
    struct TimeControllerInfo;

    /**
     * @class TimeController
     * @brief Class for managing time and delta times in the engine.
     */
    class TimeController
    {
#pragma region Constructors

    public:
        /**
         * @brief Constructs a new TimeController with the specified information.
         * @param info The TimeControllerInfo structure containing initialization parameters.
         */
        TimeController(TimeControllerInfo const &info);

        ~TimeController() = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the current unscaled time in seconds.
         * @return The unscaled time as a Float.
         */
        Timestep get_frame_timestep() const { return Timestep(m_scaledDelta, m_scaledTime); }

        /**
         * @brief Gets the current fixed timestep.
         * @return The fixed timestep as a Timestep.
         */
        Timestep get_fixed_timestep() const { return Timestep(m_fixedTimeStep, m_scaledTime - m_fixedTimeAccumulator); }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Starts the TimeController, initializing timing variables.
         */
        void start();

        /**
         * @brief Stops the TimeController.
         */
        void stop();

        /**
         * @brief Updates the TimeController, calculating delta times and updating accumulators.
         * @return The number of fixed updates performed this frame.
         */
        Int update();

        /**
         * @brief Creates a new TimeController instance.
         * @param info The TimeControllerInfo structure containing initialization parameters.
         */
        static Unique<TimeController> create(TimeControllerInfo const &info);

        /**
         * @brief Creates a new TimeController instance with default settings.
         */
        static Unique<TimeController> create();

        /**
         * @brief Gets the active Application's TimeController.
         * @return The TimeController singleton.
         */
        static TimeController &get_singleton();

#pragma endregion

#pragma region Variables

    private:
        Bool m_running;
        TimePoint m_time;
        Float m_unscaledTime;
        Float m_scaledTime;
        Float m_unscaledDelta;
        Float m_scaledDelta;
        Float m_timeScale;
        Float m_fixedTimeStep;
        Float m_fixedTimeAccumulator;
        Float m_maxAllowedTimeStep;
        Int m_maxFixedUpdatesPerFrame;

#pragma endregion
    };
}

#endif // MINTY_TIME_TIMECONTROLLER_H