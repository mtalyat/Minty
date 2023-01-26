#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds data relating to acceleration. 
	/// 
	/// Dependencies: Velocity.
	/// </summary>
	struct MINTY_API Acceleration
	{
		/// <summary>
		/// The acceleration on the X axis.
		/// </summary>
		float x;

		/// <summary>
		/// The acceleration on the Y axis.
		/// </summary>
		float y;
	};
}