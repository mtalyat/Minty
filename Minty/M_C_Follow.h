#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Follows a Target entity.
	/// </summary>
	struct Follow
	{
		/// <summary>
		/// The lerp value to the Target entity.
		/// </summary>
		float lerp;

		/// <summary>
		/// The offset to lead (or follow) the Target entity by.
		/// </summary>
		float lead;

		/// <summary>
		/// The X position.
		/// </summary>
		float x;
		/// <summary>
		/// The Y position.
		/// </summary>
		float y;

		/// <summary>
		/// Creates a new Follow component.
		/// </summary>
		/// <param name="lerp">The lerp value to the Target entity</param>
		/// <param name="lead">The offset to lead (or follow) the Target entity by</param>
		/// <param name="x">The X position</param>
		/// <param name="y">The Y position</param>
		Follow(float const lerp = 1.0f, float const lead = 1.0f, float const x = 0.0f, float const y = 0.0f)
			: lerp(lerp)
			, lead(lead)
			, x(x)
			, y(y)
		{}
	};
}