#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds velocity data.
	/// </summary>
	struct MINTY_API Velocity
	{
		/// <summary>
		/// Velocity on the X axis.
		/// </summary>
		float x;

		/// <summary>
		/// Velocity on the Y axis.
		/// </summary>
		float y;
	};
}