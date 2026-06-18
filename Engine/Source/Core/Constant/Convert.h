#pragma once

/**
 * @file Convert.h
 * @brief Header file for type conversion constants.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"

namespace Minty
{
	/**
	 * @brief The number of TimePoints in a second. This is used for converting between TimePoints and seconds.
	 */
    constexpr TimePoint ONE_NANOSECOND = 1ll;

	/**
	 * @brief The number of TimePoints in a microsecond.
	 */
	constexpr TimePoint ONE_MICROSECOND = ONE_NANOSECOND * 1000ll;

	/**
	 * @brief The number of TimePoints in a millisecond.
	 */
	constexpr TimePoint ONE_MILLISECOND = ONE_MICROSECOND * 1000ll;

	/**
	 * @brief The number of TimePoints in a second.
	 */
	constexpr TimePoint ONE_SECOND = ONE_MILLISECOND * 1000ll;

	/**
	 * @brief The number of TimePoints in a minute.
	 */
	constexpr TimePoint ONE_MINUTE = ONE_SECOND * 60ll;

	/**
	 * @brief The number of TimePoints in an hour.
	 */
	constexpr TimePoint ONE_HOUR = ONE_MINUTE * 60ll;

	/**
	 * @brief The number of bytes in a byte.
	 */
	constexpr Size B = sizeof(Byte);

	/**
	 * @brief The number of bytes in a kilobyte.
	 */
	constexpr Size KB = 1024 * B;

	/**
	 * @brief The number of bytes in a megabyte.
	 */
	constexpr Size MB = 1024 * KB;

	/**
	 * @brief The number of bytes in a gigabyte.
	 */
	constexpr Size GB = 1024 * MB;
}