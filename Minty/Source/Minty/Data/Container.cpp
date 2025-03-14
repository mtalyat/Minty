#include "pch.h"
#include "Container.h"
#include "Minty/Core/Macro.h"

using namespace Minty;

Bool Minty::Container::set(void const* const data, Size const size)
{
	// resize to new size
	if (!resize(size))
	{
		return false;
	}

	// set at 0
	set_at(data, size, 0);
	return true;
}
