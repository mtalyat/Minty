#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Represents an invalid index.
	/// </summary>
	constexpr Size INVALID_INDEX = -1;

	/// <summary>
	/// The default capacity that collections used, if not explicitly given one.
	/// </summary>
	constexpr Size DEFAULT_COLLECTION_SIZE = 16;

	/// <summary>
	/// The default threshold for rehashing a hashed collection.
	/// </summary>
	constexpr Float DEFAULT_COLLECTION_REHASH_THRESHOLD = 0.75f;

	constexpr Size COLOR_SHAMT_R = 0;
	constexpr Size COLOR_SHAMT_G = 8;
	constexpr Size COLOR_SHAMT_B = 16;
	constexpr Size COLOR_SHAMT_A = 24;

	/// <summary>
	/// The number of bytes in a byte.
	/// </summary>
	constexpr Size B = sizeof(Byte);

	/// <summary>
	/// The number of bytes in a kilobyte.
	/// </summary>
	constexpr Size KB = 1024 * B;

	/// <summary>
	/// The number of bytes in a megabyte.
	/// </summary>
	constexpr Size MB = 1024 * KB;

	/// <summary>
	/// The number of bytes in a gigabyte.
	/// </summary>
	constexpr Size GB = 1024 * MB;
}