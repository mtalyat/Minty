#pragma once

#include "M_Main.h"
#include "M_PointF.h"

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

		/// <summary>
		/// Gets the center of this Size.
		/// </summary>
		/// <returns></returns>
		PointF center() const { return PointF(width / 2.0f, height / 2.0f); }
	};
}