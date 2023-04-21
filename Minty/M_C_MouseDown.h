#pragma once

#include "M_Main.h"

#include "M_Click.h"
#include "M_Event.h"

namespace minty
{
	template class MINTY_API Event<Click const* const>;

	/// <summary>
	/// Holds data for when the mouse is pressed down on an entity.
	/// </summary>
	struct MINTY_API MouseDown
	{
		/// <summary>
		/// The event called when the mouse is pressed down on this entity.
		/// </summary>
		Event<Click const* const>* onDown;
	};
}