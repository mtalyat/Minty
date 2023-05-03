#pragma once

#include "M_Main.h"

#include "M_MouseClickEvent.h"
#include "M_Event.h"

#define mouseclick_event_t MouseClickEvent const* const
#define mouseclick_t Event<mouseclick_event_t>

namespace minty
{
	template class MINTY_API mouseclick_t;

	/// <summary>
	/// Holds data for when a mouse is clicked on the entity.
	/// </summary>
	struct MINTY_API MouseClick
	{
		/// <summary>
		/// The event to call on a successful mouse click.
		/// </summary>
		mouseclick_t* onClick;

		/// <summary>
		/// Is the entity being clicked?
		/// </summary>
		bool clicked;
	};
}