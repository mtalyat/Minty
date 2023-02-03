#pragma once

#include "M_Main.h"

#include "M_Click.h"
#include "M_Event.h"

namespace minty
{
	template class MINTY_API Event<Click const* const>;

	struct MINTY_API MouseDown
	{
		Event<Click const* const>* onDown;
	};
}