#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds scaling data.
	/// </summary>
	struct MINTY_API Scale
	{
		/// <summary>
		/// The amount of scaling on the X axis.
		/// </summary>
		float x;

		/// <summary>
		/// The amount of scaling on the Y axis.
		/// </summary>
		float y;

		Scale()
			: x(1.0f)
			, y(1.0f)
		{}
	};
}