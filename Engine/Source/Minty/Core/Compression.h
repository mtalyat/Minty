#ifndef MINTY_CORE_COMPRESSION_H
#define MINTY_CORE_COMPRESSION_H

/**
 * @file Compression.h
 * @brief Header file for data compression functions.
 * @author Mitchell Talyat
 */

#include "Minty/Core/CompressionLevel.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @brief Gets the maximum size of compressed data for a given source size.
	 */
	ULong compress_bound(ULong const sourceSize);

	/**
	 * @brief Compresses the given data from source to destination.
	 * @param destination The location to store the result.
	 * @param destinationSize The size of the number of bytes stored in the location.
	 * @param source The source of the uncompressed data.
	 * @param sourceSize The size of the uncompressed data.
	 * @param level The level to compress the data to.
	 * @return True on successful compression.
	 */
	Bool compress(Any const destination, ULong& destinationSize, AnyConst const source, ULong const sourceSize, CompressionLevel const level = CompressionLevel::Default);

	/**
	 * @brief Uncompresses the given data from source to destination.
	 * @param destination The location to store the result.
	 * @param destinationSize The size of the number of bytes stored in the location.
	 * @param source The source of the compressed data.
	 * @param sourceSize The size of the compressed data.
	 * @return True on successful uncompression.
	 */
	Bool uncompress(Any const destination, ULong& destinationSize, AnyConst const source, ULong& sourceSize);
}

#endif // MINTY_CORE_COMPRESSION_H