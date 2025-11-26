#include "pch.h"
#include "Encoding.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include <sstream>

using namespace Minty;

// TODO: different encoding direction (no size - 1 - i, etc.) for different operating systems (different endianness)

String Minty::encode_base16(void const* const data, Size const size)
{
	Byte const* const bytes = static_cast<Byte const* const>(data);

	std::stringstream ss;
	ss << std::hex << std::uppercase << std::setfill('0');
	for (Size i = 0; i < size; i++)
	{
		ss << std::setw(2) << static_cast<Int>(bytes[size - 1 - i]);
	}

	return String(ss.str().c_str());
}

void Minty::decode_base16(String const& string, void* const data, Size const size)
{
	MINTY_ASSERT(string.get_size() % 2 == 0, ErrorCode::Argument_InvalidFormat);
	MINTY_ASSERT(size == string.get_size() / 2, ErrorCode::Argument_InvalidSize);

	Byte* const bytes = static_cast<Byte* const>(data);
	
	// get the string data
	Char buffer[3] = { 0, 0, 0 };
	for (Size i = 0; i < size; ++i)
	{
		// copy characters to buffer
		memcpy(buffer, string.get_data() + ((size - 1 - i) * 2), sizeof(Char) * 2);
		// convert to byte
		bytes[i] = static_cast<Byte>(std::stoul(buffer, nullptr, 16));
	}
}
