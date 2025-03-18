#include "pch.h"
#include "Encoding.h"

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
	MINTY_ASSERT(string.get_size() % 2 == 0, "The given string is not a valid base16 string.");
	MINTY_ASSERT(size == string.get_size() / 2, "The given size does not match the string size.");

	Byte* const bytes = static_cast<Byte* const>(data);
	
	// get the string data
	Char buffer[3] = { 0, 0, 0 };
	for (Long i = 0; i < size; ++i)
	{
		// copy characters to buffer
		memcpy(buffer, string.get_data() + ((size - 1 - i) * 2), sizeof(Char) * 2);
		// convert to byte
		bytes[i] = static_cast<Byte>(std::stoul(buffer, nullptr, 16));
	}
}
