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
		RectF hitbox;
	};
}