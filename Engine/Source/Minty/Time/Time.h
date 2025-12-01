#ifndef MINTY_TIME_TIME_H
#define MINTY_TIME_TIME_H

/**
 * @file Time.h
 * @brief Header file defining the Time utility class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/**
	 * @class Time
	 * @brief Time utility class.
	 */
	class Time
	{
#pragma region Constructors

	public:
		Time() = delete;
		~Time() = delete;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Get the current high-resolution time in nanoseconds since epoch.
		 * @return Current time in nanoseconds.
		 */
		static TimePoint get_time();

		/**
		 * @brief Get the current system clock time in nanoseconds since epoch.
		 * @return Current system clock time in nanoseconds.
		 */
		static TimePoint get_system_time();

		/**
		 * @brief Format a time value (in nanoseconds) into a human-readable string.
		 * @param time The time value in nanoseconds.
		 * @return Formatted time string.
		 */
		static String format(TimePoint const time);

		/**
		 * @brief Get the current timestamp as a formatted string.
		 * @return Current timestamp string.
		 */
		static String get_timestamp();

#pragma endregion
	};
}

#endif // MINTY_TIME_TIME_H