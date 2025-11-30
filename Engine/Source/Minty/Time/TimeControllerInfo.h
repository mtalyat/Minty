#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a TimeManager.
	/// </summary>
	struct TimeControllerInfo
	{
		/// <summary>
		/// The fixed time step in seconds.
		/// </summary>
		Float fixedTimeStep = 0.02f;

		/// <summary>
		/// The maximum allowed time step in seconds.
		/// </summary>
		Float maxAllowedTimeStep = 0.25f;

		/// <summary>
		/// The maximum number of fixed updates to perform per frame.
		/// </summary>
		Int maxFixedUpdatesPerFrame = 5;
	};
}