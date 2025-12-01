#ifndef MINTY_TIME_TIMECONTROLLERINFO_H
#define MINTY_TIME_TIMECONTROLLERINFO_H

/**
 * @file TimeControllerInfo.h
 * @brief Header file defining the TimeControllerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @brief The arguments for a TimeManager.
	 */
	struct TimeControllerInfo
	{
		/**
		 * @brief The fixed time step in seconds.
		 */
		Float fixedTimeStep = 0.02f;

		/**
		 * @brief The maximum allowed time step in seconds.
		 */
		Float maxAllowedTimeStep = 0.25f;

		/**
		 * @brief The maximum number of fixed updates to perform per frame.
		 */
		Int maxFixedUpdatesPerFrame = 5;
	};
}

#endif // MINTY_TIME_TIMECONTROLLERINFO_H