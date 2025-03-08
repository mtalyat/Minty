#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
#pragma region Color

	constexpr Size COLOR_SHAMT_R = 0;
	constexpr Size COLOR_SHAMT_G = 8;
	constexpr Size COLOR_SHAMT_B = 16;
	constexpr Size COLOR_SHAMT_A = 24;

#pragma endregion

#pragma region Defaults

	/// <summary>
	/// The default capacity that collections used, if not explicitly given one.
	/// </summary>
	constexpr Size DEFAULT_COLLECTION_SIZE = 16;

	/// <summary>
	/// The default threshold for rehashing a hashed collection.
	/// </summary>
	constexpr Float DEFAULT_COLLECTION_REHASH_THRESHOLD = 0.75f;

#pragma endregion

#pragma region Extensions

	constexpr Char const* EXTENSION_WRAP = ".wrap";

#pragma endregion

#pragma region Indexing

	/// <summary>
	/// Represents an invalid index.
	/// </summary>
	constexpr Size INVALID_INDEX = -1;

#pragma endregion

#pragma region Units of Measurement

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

#pragma endregion

#pragma region Wrap

	/// <summary>
	/// The first bytes in any Wrap file.
	/// </summary>
	constexpr Char const* WRAP_MAGIC = "WRAP";

	/// <summary>
	/// The number of magic bytes in a Wrap file.
	/// </summary>
	constexpr Size WRAP_MAGIC_SIZE = 4;

	/// <summary>
	/// The maximum size of a Wrap header path.
	/// </summary>
	constexpr Size const WRAP_HEADER_PATH_SIZE = 100;

	/// <summary>
	/// The maximum size of a Wrap header name.
	/// </summary>
	constexpr Size const WRAP_HEADER_NAME_SIZE = 50;

	/// <summary>
	/// The maximum size of a Wrap entry path.
	/// </summary>
	constexpr Size const WRAP_ENTRY_PATH_SIZE = 255;

	/// <summary>
	/// The current Wrap version.
	/// </summary>
	constexpr uint16_t const WRAP_VERSION = 0;

#pragma endregion

}