#pragma once

#include "M_Main.h"

#include "M_MouseClickEvent.h"
#include "M_Event.h"

namespace minty
{
	template class MINTY_API Event<MouseClickEvent const* const>;

	/// <summary>
	/// Holds data for when the mouse is released on an entity.
	/// </summary>
	struct MINTY_API MouseUp
	{
		/// <summary>
		/// The event called when the mouse is released on this entity.
		/// </summary>
		Event<MouseClickEvent const* const>* onUp;
	};
}