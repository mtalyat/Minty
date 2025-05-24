#include "pch.h"
#include "Container.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

Bool Minty::Container::set(void const* const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, "Cannot set nullptr data.");
	MINTY_ASSERT(size > 0, "Cannot set data without a size.");

	// resize to new size
	if (!resize(size))
	{
		return false;
	}

	// set at 0
	set_at(data, size, 0);
	return true;
}
