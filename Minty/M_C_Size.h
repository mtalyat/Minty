#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component that holds size data.
	/// </summary>
	struct MINTY_API Size
	{
		/// <summary>
		/// The size of the entity on the X axis.
		/// </summary>
		float width;

		/// <summary>
		/// The size of the entity on the Y axis.
		/// </summary>
		float height;
	};
}