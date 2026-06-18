#include "pch.h"
#include "Encoding.h"
#include "Core/Tool/Format.h"
#include "Core/Debug/Debug.h"
#include <sstream>

using namespace Minty;

// MAYBE TODO: different encoding direction (no size - 1 - i, etc.) for different operating systems (different endianness)

void Minty::encode_base16(PointerConst const data, Size const size, Char *const buffer, Size const bufferSize)
{
	MINTY_ASSERT(bufferSize >= size * 2, ErrorCodeEnum::Argument_InvalidSize);

	Byte const* const bytes = static_cast<Byte const* const>(data);

	std::stringstream ss;
	ss << std::hex << std::uppercase << std::setfill('0');
	for (Size i = 0; i < size; i++)
	{
		ss << std::setw(2) << static_cast<Int>(bytes[size - 1 - i]);
	}

	std::string str = ss.str();

	memcpy(buffer, str.c_str(), str.size());
	buffer[str.size()] = '\0';
}

void Minty::decode_base16(Char const *const data, Size const size, Pointer const buffer, Size const bufferSize)
{
	MINTY_ASSERT(size % 2 == 0, ErrorCodeEnum::Argument_InvalidFormat);
	Size const groupSize = size / 2;
	MINTY_ASSERT(bufferSize >= groupSize, ErrorCodeEnum::Argument_InvalidSize);

	Byte* const bytes = static_cast<Byte* const>(buffer);
	
	// get the string data
	Char tempBuffer[3] = { 0, 0, 0 };
	for (Size i = 0; i < groupSize; ++i)
	{
		// copy characters to buffer
		tempBuffer[0] = data[size - 2 - i * 2];
		tempBuffer[1] = data[size - 1 - i * 2];
		
		// convert to byte
		bytes[i] = static_cast<Byte>(std::stoul(tempBuffer, nullptr, 16));
	}
}
