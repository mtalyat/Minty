#pragma once
#include "Minty/Time/Time.h"

namespace Minty
{
	struct TimeManagerBuilder;

	/// <summary>
	/// Manages the time for the application.
	/// </summary>
	class TimeManager
	{
#pragma region Variables

	private:
		Float m_time; // total time in seconds
		Float m_rawTime; // unscaled total time in seconds
		Float m_elapsed; // elapsed time since last frame in seconds
		Float m_rawElapsed; // unscaled elapsed time since last frame in seconds
		Float m_timeScale;
		Float m_fixedTimeStep;
		Float m_fixedTimeAccumulator;
		Float m_maxAllowedTimeStep;
		Int m_maxFixedUpdatesPerFrame;

#pragma endregion

#pragma region Constructors

	public:
		TimeManager(TimeManagerBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Returns a Time value representing the frame time.
		/// </summary>
		/// <returns>The Time value.</returns>
		Time get_frame_time() const
		{
			return Time(m_time, m_elapsed);
		}

		/// <summary>
		/// Returns a Time value representing the fixed time step.
		/// </summary>
		/// <returns>The Time value.</returns>
		Time get_fixed_time() const
		{
			return Time(m_time - m_fixedTimeAccumulator, m_fixedTimeStep);
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Processes the frame time and returns the number of fixed updates to perform.
		/// </summary>
		/// <param name="deltaTime">The time that has elapsed since last frame.</param>
		/// <returns>The number of fixed updates to perform.</returns>
		Int update(Float const deltaTime);

#pragma endregion


	};
}