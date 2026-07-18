#include "pch.hpp"
#include "Container.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Bool Minty::Container::set(PointerConst const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	// resize to new size
	if (!resize(size))
	{
		return false;
	}

	// set at 0
	set_at(data, size, 0);
	return true;
}
