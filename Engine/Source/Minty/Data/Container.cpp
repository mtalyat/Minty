#include "pch.h"
#include "Container.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Bool Minty::Container::set(AnyConst const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedNonZero);

	// resize to new size
	if (!resize(size))
	{
		return false;
	}

	// set at 0
	set_at(data, size, 0);
	return true;
}
