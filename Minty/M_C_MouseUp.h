#pragma once

#include "M_Main.h"

#include "M_Click.h"
#include "M_Event.h"

namespace minty
{
	template class MINTY_API Event<Click const* const>;

	/// <summary>
		/// Holds data for when the mouse is released on an entity.
		/// </summary>
	struct MINTY_API MouseUp
	{
		Event<Click const* const>* onUp;
	};
}