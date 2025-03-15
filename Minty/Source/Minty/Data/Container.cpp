#include "pch.h"
#include "Container.h"
#include "Minty/Core/Macro.h"

using namespace Minty;

Bool Minty::Container::set(void const* const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, "Cannot set nullptr data.");
	MINTY_ASSERT(size > 0, "Cannot set data without a size.");
	MINTY_ASSERT(size <= get_size(), "Cannot set data that exceeds the size of the container.");

	// resize to new size
	if (!resize(size))
	{
		return false;
	}

	// set at 0
	set_at(data, size, 0);
	return true;
}
