#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Follows a Target entity.
	/// </summary>
	struct Follow
	{
		float lerp;

		float lead;

		float x, y;

		Follow(float const lerp = 1.0f, float const lead = 1.0f, float const x = 0.0f, float const y = 0.0f)
			: lerp(lerp)
			, lead(lead)
			, x(x)
			, y(y)
		{}
	};
}