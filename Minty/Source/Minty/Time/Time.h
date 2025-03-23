#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/// <summary>
	/// Holds total and elapsed time values.
	/// </summary>
	class Time
	{
#pragma region Variables

	private:
		Float m_total;
		Float m_elapsed;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Time object.
		/// </summary>
		Time()
			: m_total(0.0f)
			, m_elapsed(0.0f)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the total time elapsed in seconds.
		/// </summary>
		/// <returns>The time in seconds.</returns>
		inline Float get_total() const { return m_total; }

		/// <summary>
		/// Sets the total time elapsed in seconds.
		/// </summary>
		/// <param name="total">The new time in seconds.</param>
		inline void set_total(Float const total) { m_total = total; }

		/// <summary>
		/// Gets the time elapsed since the last frame in seconds.
		/// </summary>
		/// <returns>The time in seconds.</returns>
		inline Float get_elapsed() const { return m_elapsed; }

		/// <summary>
		/// Sets the time elapsed since the last frame in seconds.
		/// </summary>
		/// <param name="elapsed">The new time in seconds.</param>
		inline void set_elapsed(Float const elapsed) { m_elapsed = elapsed; }

		/// <summary>
		/// Sets the total and elapsed time values.
		/// </summary>
		/// <param name="total">The total time.</param>
		/// <param name="elapsed">The elapsed time.</param>
		inline void update(Float const total, Float const elapsed)
		{
			m_total = total;
			m_elapsed = elapsed;
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the TimePoint for now.
		/// </summary>
		/// <returns>The current time.</returns>
		static TimePoint now();

		/// <summary>
		/// Gets the duration between start and end in seconds.
		/// </summary>
		/// <param name="start">The starting TimePoint.</param>
		/// <param name="end">The ending TimePoint.</param>
		/// <returns>The duration in seconds.</returns>
		static Float calculate_duration_seconds(TimePoint const start, TimePoint const end);

		/// <summary>
		/// Gets the current time as a time stamp string.
		/// </summary>
		/// <returns>The timestamp.</returns>
		static String timestamp();

		/// <summary>
		/// Sleeps for the given number of nanoseconds.
		/// </summary>
		/// <param name="time">The number of nanoseconds.</param>
		static void sleep(TimeElapsed const time);

#pragma endregion
	};
}