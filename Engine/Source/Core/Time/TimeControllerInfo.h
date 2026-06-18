#pragma once

/**
 * @file TimeControllerInfo.h
 * @brief Header file defining the TimeControllerInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"

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
		Float fixedTimestep = 0.02f;

		/**
		 * @brief The maximum allowed time step in seconds.
		 */
		Float maxAllowedTimestep = 0.25f;

		/**
		 * @brief The maximum number of fixed updates to perform per frame.
		 */
		Int maxFixedUpdatesPerFrame = 5;
	};
}