#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds positional data.
	/// </summary>
	struct MINTY_API Position
	{
		/// <summary>
		/// The X position within the Scene.
		/// </summary>
		float x;

		/// <summary>
		/// The Y position within the Scene.
		/// </summary>
		float y;
	};
}