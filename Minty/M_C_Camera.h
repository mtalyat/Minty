#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds data relating a camera within the Scene. 
	/// 
	/// Dependencies: Velocity.
	/// </summary>
	struct MINTY_API Camera
	{
		/// <summary>
		/// The in and out zoom the Camera has. 1.0f is normal, higher values means more zoom.
		/// </summary>
		float zoom;
	};
}