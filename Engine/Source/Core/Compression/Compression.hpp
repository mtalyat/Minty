#pragma once

/**
 * @file Compression.hpp
 * @brief Header file for data compression functions.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "CompressionLevel.hpp"

namespace Minty
{
	/**
	 * @brief Gets the maximum size of compressed data for a given source size.
	 */
	WUInt compress_bound(WUInt const sourceSize);

	/**
	 * @brief Compresses the given data from source to destination.
	 * @param destination The location to store the result.
	 * @param destinationSize The size of the number of bytes stored in the location.
	 * @param source The source of the uncompressed data.
	 * @param sourceSize The size of the uncompressed data.
	 * @param level The level to compress the data to.
	 * @return True on successful compression.
	 */
	Bool compress(Pointer const destination, WUInt& destinationSize, PointerConst const source, WUInt const sourceSize, CompressionLevelEnum const level = CompressionLevelEnum::Default);

	/**
	 * @brief Uncompresses the given data from source to destination.
	 * @param destination The location to store the result.
	 * @param destinationSize The size of the number of bytes stored in the location.
	 * @param source The source of the compressed data.
	 * @param sourceSize The size of the compressed data.
	 * @return True on successful uncompression.
	 */
	Bool uncompress(Pointer const destination, WUInt& destinationSize, PointerConst const source, WUInt& sourceSize);
}
