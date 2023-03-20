#pragma once

#include "M_Main.h"

namespace minty
{
	constexpr float GRAVITY = 9.81f;

	/// <summary>
	/// A component that will apply gravity to the velocity component associated with the entity.
	/// </summary>
	struct MINTY_API Gravity
	{
		float scale;

		Gravity(float const s = GRAVITY)
			: scale(s)
		{}
	};
}