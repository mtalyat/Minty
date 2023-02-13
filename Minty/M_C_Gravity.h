#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that will apply gravity to the velocity component associated with the entity.
	/// </summary>
	struct MINTY_API Gravity
	{
		float scale;

		Gravity(float const s = 1.0f)
			: scale(s)
		{}
	};
}