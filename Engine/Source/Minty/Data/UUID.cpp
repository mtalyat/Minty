#include "pch.h"
#include "UUID.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Core/Math.h"

using namespace Minty;

Minty::UUID::UUID()
	: m_data(0)
{
}

Minty::UUID::UUID(Byte const (&id)[UUID_BYTE_SIZE])
	: m_data(0)
{
	for (Size i = 0; i < UUID_BYTE_SIZE; ++i)
	{
		m_data[i] = id[i];
	}
}

Minty::UUID::UUID(UInt64 const id_low, UInt64 const id_high)
	: m_data(0)
{
	std::memcpy(m_data, &id_low, sizeof(UInt64));
	std::memcpy(m_data + sizeof(UInt64), &id_high, sizeof(UInt64));
}

Minty::UUID::UUID(StringView const &string)
	: m_data(0)
{
	if (string.is_empty())
	{
		return;
	}

	Bool const parseResult = parse(string);
	MINTY_ASSERT_F(parseResult, ErrorCode::Serialization_InvalidFormat, string);
}

UUID Minty::UUID::create()
{
	UInt64 randomValues[2];
	randomValues[0] = Math::random_ulong();
	randomValues[1] = Math::random_ulong();
	return UUID(reinterpret_cast<Byte const(&)[UUID_BYTE_SIZE]>(randomValues));
}

void Minty::UUID::clear()
{
	std::memset(m_data, 0, UUID_BYTE_SIZE);
}

Bool Minty::UUID::parse(StringView const text)
{
	// check if empty or "NULL"
	if (text.is_empty())
	{
		clear();
		return true;
	}

	if (text == "NULL" || text == "null")
	{
		clear();
		return true;
	}

	// check if the string is a valid UUID
	if (text.get_size() != UUID_HEX_SIZE_FULL && text.get_size() != UUID_HEX_SIZE_HALF)
	{
		return false;
	}

	// if the size is incorrect, return invalid UUID
	Size const size = text.get_size();
	if (size == UUID_HEX_SIZE_FULL)
	{
		// full UUID string
		decode_base16(text.get_data(), text.get_size(), m_data, sizeof(Byte) * UUID_BYTE_SIZE);
	}
	else if (size == UUID_HEX_SIZE_HALF)
	{
		// short UUID string
		std::memset(m_data + UUID_BYTE_SIZE_HALF, 0, UUID_BYTE_SIZE_HALF);
		decode_base16(text.get_data(), text.get_size(), m_data, UUID_BYTE_SIZE_HALF);
	}
	else
	{
		MINTY_ABORT(ErrorCode::Serialization_InvalidFormat);
	}

	return true;
}

String Minty::UUID::to_string() const
{
	// if the high bits are zero, return the short version
	if (*static_cast<UInt64 const *>(static_cast<void const *>(m_data + UUID_BYTE_SIZE_HALF)) == 0)
	{
		Char buffer[UUID_HEX_SIZE_HALF + 1];
		encode_base16(m_data, UUID_BYTE_SIZE_HALF, buffer, sizeof(buffer));
		buffer[UUID_HEX_SIZE_HALF] = '\0';
		return String(buffer);
	}
	else
	{
		Char buffer[UUID_HEX_SIZE_FULL + 1];
		encode_base16(m_data, UUID_BYTE_SIZE, buffer, sizeof(buffer));
		buffer[UUID_HEX_SIZE_FULL] = '\0';
		return String(buffer);
	}
}
