#pragma once

#include "M_Main.h"
#include "M_Event.h"
#include "M_MouseMoveEvent.h"

namespace minty
{
	template class MINTY_API Event<MouseMoveEvent const* const>;

	struct MINTY_API MouseExit
	{
		Event<MouseMoveEvent const* const>* onExit;
	};
}