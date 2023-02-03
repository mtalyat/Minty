#pragma once

#include "M_Main.h"

#include "M_Click.h"
#include "M_Event.h"

namespace minty
{
	template class MINTY_API Event<Click const* const>;

	/// <summary>
	/// Holds data for when a mouse is clicked on the entity.
	/// </summary>
	struct MINTY_API MouseClick
	{
		Event<Click const* const>* onClick;

		bool clicked;
	};
}