#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Holds two normalized values that can be used to identify the center of something.
	/// </summary>
	struct MINTY_API Center
	{
		/// <summary>
		/// The normalized X value.
		/// </summary>
		float x;
		/// <summary>
		/// The normalized Y value.
		/// </summary>
		float y;
	};
}