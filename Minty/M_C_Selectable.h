#pragma once

#include "M_Main.h"
#include "M_Event.h"
#include "entt.hpp"

namespace minty
{
	struct MINTY_API Selectable
	{
		int index;

		Event<>* onSelect;

		Event<>* onDeselect;
	};
}