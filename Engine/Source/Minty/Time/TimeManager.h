#pragma once
#include "Minty/Time/Time.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	struct TimeManagerInfo;

    /**
     * @class TimeManager
     * @brief Class for managing time and delta times in the engine.
     */
    class TimeManager
    {
#pragma region Constructors

    public:
        /**
         * @brief Constructs a new TimeManager with the specified information.
         * @param info The TimeManagerInfo structure containing initialization parameters.
         */
        TimeManager(TimeManagerInfo const &info);

        ~TimeManager() = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the current unscaled time in seconds.
         * @return The unscaled time as a Float.
         */
        Timestep get_frame_timestep() const { return Timestep(m_scaledDelta, m_scaledTime);}

        /**
         * @brief Gets the current fixed timestep.
         * @return The fixed timestep as a Timestep.
         */
        Timestep get_fixed_timestep() const { return Timestep(m_fixedTimeStep, m_scaledTime - m_fixedTimeAccumulator); }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Starts the time manager, initializing timing variables.
         */
        void start();

        /**
         * @brief Stops the time manager.
         */
        void stop();

        /**
         * @brief Updates the time manager, calculating delta times and updating accumulators.
         * @return The number of fixed updates performed this frame.
         */
        Int update();

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