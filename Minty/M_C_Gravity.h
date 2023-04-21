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
		/// <summary>
		/// The amount to scale the gravity by.
		/// </summary>
		float scale;

		/// <summary>
		/// Creates a new Gravity component.
		/// </summary>
		/// <param name="s"></param>
		Gravity(float const s = 1.0f)
			: scale(s)
		{}
	};
}