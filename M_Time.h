#pragma once

#include "M_Main.h"
#include <ctime>

namespace minty
{
	class MINTY_API Time
	{
	private:
		static float s_deltaTime;

		static clock_t s_deltaTimeRaw;

		static float s_timeScale;

	public:
		/// <summary>
		/// Gets the time that elapsed over the previous frame, unaltered by time scale.
		/// </summary>
		/// <returns></returns>
		inline static float deltaTimeUnscaled();

		/// <summary>
		/// Gets the time that elapsed over the previous frame, multiplied by the time scale.
		/// </summary>
		/// <returns></returns>
		inline static float deltaTime();

		/// <summary>
		/// Gets the raw time elapsed over the previous frame, as milliseconds clock_t.
		/// </summary>
		/// <returns></returns>
		inline static clock_t deltaTimeRaw();

		/// <summary>
		/// Sets the delta time from the most recent frame.
		/// </summary>
		/// <param name="time"></param>
		static void setDeltaTime(long const time);

		/// <summary>
		/// Gets the time scale.
		/// </summary>
		/// <returns></returns>
		inline static float timeScale();

		/// <summary>
		/// Sets the time scale.
		/// </summary>
		/// <param name="scale"></param>
		inline static void setTimeScale(float const scale);

		/// <summary>
		/// Gets the current time in clock_t milliseconds.
		/// </summary>
		/// <returns></returns>
		inline static clock_t time();
	};
}