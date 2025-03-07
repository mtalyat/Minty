#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	constexpr Size INVALID_INDEX = -1;

	constexpr Size DEFAULT_COLLECTION_SIZE = 16;
	constexpr Float DEFAULT_COLLECTION_REHASH_THRESHOLD = 0.75f;

	constexpr Size B = sizeof(Byte);
	constexpr Size KB = 1024 * B;
	constexpr Size MB = 1024 * KB;
	constexpr Size GB = 1024 * MB;
}