#pragma once

#include "M_Main.h"

#include "M_RectF.h"

namespace minty
{
	/// <summary>
	/// Marks an object as able to receive mouse clicks.
	/// </summary>
	struct MINTY_API Clickable
	{
		/// <summary>
		/// The hitbox that the mouse must click inside of.
		/// </summary>
		RectF hitbox;

		/// <summary>
		/// The mouse must click on a pixel with an alpha > 0, if true.
		/// </summary>
		bool pixelPerfect;
	};
}