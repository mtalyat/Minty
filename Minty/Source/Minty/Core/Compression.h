#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Determines when to compress data being stored in a wrap file.
	/// </summary>
	enum class CompressionLevel : Int
	{
		Level0 = 0,
		Level1 = 1,
		Level2 = 2,
		Level3 = 3,
		Level4 = 4,
		Level5 = 5,
		Level6 = 6,
		Level7 = 7,
		Level8 = 8,
		Level9 = 9,

		/// <summary>
		/// Do not compress the data.
		/// </summary>
		None = Level0,

		/// <summary>
		/// Lightly compresses the data, quickly.
		/// </summary>
		Fast = Level1,
		/// <summary>
		/// Heavily compresses the data, slowly.
		/// </summary>
		Slow = Level9,

		/// <summary>
		/// Lightly compress the data.
		/// </summary>
		Low = Level1,
		/// <summary>
		/// Heavily compress the data.
		/// </summary>
		High = Level9,

		/// <summary>
		/// Default compression.
		/// </summary>
		Default = Level6,
	};

	/// <summary>
	/// Given the size of the uncompressed data, returns the maximum size of the compressed data array.
	/// </summary>
	/// <param name="sourceSize">The size of the uncompressed data.</param>
	/// <returns>The size of the compressed data array, in bytes.</returns>
	ULong compress_bound(ULong const sourceSize);

	/// <summary>
	/// Compresses the given data from source to destination.
	/// </summary>
	/// <param name="destination">The location to store the result.</param>
	/// <param name="destinationSize">The size of the number of bytes stored in the location.</param>
	/// <param name="source">The source of the uncompressed data.</param>
	/// <param name="sourceSize">The size of the uncompressed data.</param>
	/// <param name="level">The level to compress the data to.</param>
	/// <returns>True on successful compression.</returns>
	Bool compress(void* const destination, ULong& destinationSize, void* const source, ULong const sourceSize, CompressionLevel const level = CompressionLevel::Default);

	/// <summary>
	/// Uncompresses the given data from source to destination.
	/// </summary>
	/// <param name="destination">The location to store the result.</param>
	/// <param name="destinationSize">The size of the number of bytes stored in the location.</param>
	/// <param name="source">The source of the compressed data.</param>
	/// <param name="sourceSize">The size of the compressed data.</param>
	/// <returns>True on successful uncompression.</returns>
	Bool uncompress(void* const destination, ULong& destinationSize, void* const source, ULong& sourceSize);
}