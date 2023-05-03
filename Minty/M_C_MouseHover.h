#pragma once

#include "M_Main.h"
#include "M_Event.h"
#include "M_MouseMoveEvent.h"

namespace minty
{
	struct MINTY_API MouseHover
	{
		/// <summary>
		/// True when the mouse is hovering over this entity.
		/// </summary>
		bool hovering;
	};
}