#include "pch.h"
#include "Compression.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include <zlib.h>

using namespace Minty;

ULong Minty::compress_bound(ULong const sourceSize)
{
	return compressBound(static_cast<uLong>(sourceSize));
}

Bool Minty::compress(Any const destination, ULong& destinationSize, AnyConst const source, ULong const sourceSize, CompressionLevel const level)
{
	MINTY_ASSERT(destination, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCode::Argument_ExpectedNonNull);

	int const result = compress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef const*>(source), static_cast<uLong>(sourceSize), static_cast<int>(level));

	MINTY_ASSERT(result != Z_BUF_ERROR, ErrorCode::Argument_InvalidSize); // "Destination buffer is too small to hold the compressed data."
	MINTY_ASSERT(result != Z_MEM_ERROR, ErrorCode::Memory_AllocationFailed); // "Not enough memory to perform compression."
	MINTY_ASSERT(result != Z_STREAM_ERROR, ErrorCode::Argument_InvalidValue); // "Invalid compression level."

	return result == Z_OK;
}

Bool Minty::uncompress(Any const destination, ULong& destinationSize, AnyConst const source, ULong& sourceSize)
{
	MINTY_ASSERT(destination, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCode::Argument_ExpectedNonNull);

	int const result = uncompress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef const*>(source), reinterpret_cast<uLong*>(&sourceSize));

	MINTY_ASSERT(result != Z_BUF_ERROR, ErrorCode::Argument_InvalidSize); // "Destination buffer is too small to hold the uncompressed data."
	MINTY_ASSERT(result != Z_MEM_ERROR, ErrorCode::Memory_AllocationFailed); // "Not enough memory to perform uncompression."
	MINTY_ASSERT(result != Z_DATA_ERROR, ErrorCode::Argument_InvalidFormat); // "The input data was corrupted or incomplete."

	return result == Z_OK;
}
