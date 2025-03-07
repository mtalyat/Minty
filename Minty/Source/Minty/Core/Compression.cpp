#include "pch.h"
#include "Compression.h"
#include <zlib.h>

using namespace Minty;

ULong Minty::compress_bound(ULong const sourceSize)
{
	return compressBound(sourceSize);
}

ErrorCode Minty::compress(void* const destination, ULong& destinationSize, void* const source, ULong const sourceSize, CompressionLevel const level)
{
	int result = compress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), sourceSize, static_cast<int>(level));

	if (result == Z_OK)
	{
		return ErrorCode::Success;
	}

	return ErrorCode::Failure;
}

ErrorCode Minty::uncompress(void* const destination, ULong& destinationSize, void* const source, ULong& sourceSize)
{
	int result = uncompress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), reinterpret_cast<uLong*>(&sourceSize));

	if (result == Z_OK)
	{
		return ErrorCode::Success;
	}

	return ErrorCode::Failure;
}
