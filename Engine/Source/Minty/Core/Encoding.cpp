#include "pch.h"
#include "Encoding.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include <sstream>

using namespace Minty;

// MAYBE TODO: different encoding direction (no size - 1 - i, etc.) for different operating systems (different endianness)

void Minty::encode_base16(AnyConst const data, Size const size, Char *const buffer, Size const bufferSize)
{
	MINTY_ASSERT(bufferSize >= size * 2, ErrorCode::Argument_InvalidSize);

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

void Minty::decode_base16(Char const *const data, Size const size, Any const buffer, Size const bufferSize)
{
	MINTY_ASSERT(size % 2 == 0, ErrorCode::Argument_InvalidFormat);
	Size const groupSize = size / 2;
	MINTY_ASSERT(bufferSize >= groupSize, ErrorCode::Argument_InvalidSize);

	Byte* const bytes = static_cast<Byte* const>(buffer);
	
	// get the string data
	Char tempBuffer[3] = { 0, 0, 0 };
	for (Size i = 0; i < groupSize; ++i)
	{
		// copy characters to buffer
		memcpy(tempBuffer, data + ((size - 1 - i) * 2), sizeof(Char) * 2);
		// convert to byte
		bytes[i] = static_cast<Byte>(std::stoul(tempBuffer, nullptr, 16));
	}
}
