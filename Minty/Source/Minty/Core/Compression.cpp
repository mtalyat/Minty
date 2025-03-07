#include "pch.h"
#include "Compression.h"
#include "Minty/Core/Macro.h"
#include <zlib.h>

using namespace Minty;

ULong Minty::compress_bound(ULong const sourceSize)
{
	return compressBound(sourceSize);
}

Bool Minty::compress(void* const destination, ULong& destinationSize, void* const source, ULong const sourceSize, CompressionLevel const level)
{
	MINTY_ASSERT(destination, "Destination buffer is null.");
	MINTY_ASSERT(source, "Source buffer is null.");

	int result = compress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), sourceSize, static_cast<int>(level));

	return result == Z_OK;
}

Bool Minty::uncompress(void* const destination, ULong& destinationSize, void* const source, ULong& sourceSize)
{
	MINTY_ASSERT(destination, "Destination buffer is null.");
	MINTY_ASSERT(source, "Source buffer is null.");

	int result = uncompress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), reinterpret_cast<uLong*>(&sourceSize));

	return result == Z_OK;
}
