#include "pch.h"
#include "Compression.h"
#include "Core/Tool/Format.h"
#include "Core/Debug/Debug.h"
#include "Library/ZLib/ZLib.h"

using namespace Minty;

WUInt Minty::compress_bound(WUInt const sourceSize)
{
	return compressBound(static_cast<uLong>(sourceSize));
}

Bool Minty::compress(Pointer const destination, WUInt& destinationSize, PointerConst const source, WUInt const sourceSize, CompressionLevelEnum const level)
{
	MINTY_ASSERT(destination, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCodeEnum::Argument_ExpectedNonNull);

	int const result = compress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef const*>(source), static_cast<uLong>(sourceSize), static_cast<int>(level));

	MINTY_ASSERT(result != Z_BUF_ERROR, ErrorCodeEnum::Argument_InvalidSize); // "Destination buffer is too small to hold the compressed data."
	MINTY_ASSERT(result != Z_MEM_ERROR, ErrorCodeEnum::Memory_AllocationFailed); // "Not enough memory to perform compression."
	MINTY_ASSERT(result != Z_STREAM_ERROR, ErrorCodeEnum::Argument_InvalidValue); // "Invalid compression level."

	return result == Z_OK;
}

Bool Minty::uncompress(Pointer const destination, WUInt& destinationSize, PointerConst const source, WUInt& sourceSize)
{
	MINTY_ASSERT(destination, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(source, ErrorCodeEnum::Argument_ExpectedNonNull);

	int const result = uncompress2(static_cast<Bytef*>(destination), reinterpret_cast<uLongf*>(&destinationSize), static_cast<Bytef const*>(source), reinterpret_cast<uLong*>(&sourceSize));

	MINTY_ASSERT(result != Z_BUF_ERROR, ErrorCodeEnum::Argument_InvalidSize); // "Destination buffer is too small to hold the uncompressed data."
	MINTY_ASSERT(result != Z_MEM_ERROR, ErrorCodeEnum::Memory_AllocationFailed); // "Not enough memory to perform uncompression."
	MINTY_ASSERT(result != Z_DATA_ERROR, ErrorCodeEnum::Argument_InvalidFormat); // "The input data was corrupted or incomplete."

	return result == Z_OK;
}
