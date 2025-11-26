#include "pch.h"
#include "Compression.h"
#include "Minty/Core/Format.h"x
#include "Minty/Debug/Debug.h"
#include <zlib.h>

using namespace Minty;

ULong Minty::compress_bound(ULong const sourceSize)
{
	return compressBound(static_cast<uLong>(sourceSize));
}

Bool Minty::compress(void* const destination, ULong& destinationSize, void* const source, ULong const sourceSize, CompressionLevel const level)
{
	MINTY_ASSERT(destination, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCode::Argument_ExpectedNonNull);

	int result = compress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), static_cast<uLong>(sourceSize), static_cast<int>(level));

	return result == Z_OK;
}

Bool Minty::uncompress(void* const destination, ULong& destinationSize, void* const source, ULong& sourceSize)
{
	MINTY_ASSERT(destination, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCode::Argument_ExpectedNonNull);

	int result = uncompress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef*>(source), reinterpret_cast<uLong*>(&sourceSize));

	return result == Z_OK;
}
