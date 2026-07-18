#pragma once

/**
 * @file Time.h
 * @brief Header file defining the Time utility class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/String.hpp"

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
		 * @brief Format a TimePoint into a human-readable string.
		 * @param time The TimePoint to format.
		 * @return Formatted time string.
		 */
		static void format(TimePoint const time, Char* const buffer, Size const bufferSize);

		/**
		 * @brief Get the current timestamp as a formatted string.
		 * @return Current timestamp string.
		 */
		static String get_timestamp();

#pragma endregion
	};
}