#include "pch.h"
#include "UUID.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Core/Math.h"

using namespace Minty;

Minty::UUID::UUID()
	: m_id(0)
{
}

Minty::UUID::UUID(Byte const (&id)[UUID_BYTE_SIZE])
	: m_id(0)
{
	for (Size i = 0; i < UUID_BYTE_SIZE; ++i)
	{
		m_id[i] = id[i];
	}
}

Minty::UUID::UUID(UInt64 const id_high, UInt64 const id_low)
	: m_id(0)
{
	std::memcpy(m_id, &id_high, sizeof(UInt64));
	std::memcpy(m_id + sizeof(UInt64), &id_low, sizeof(UInt64));
}

Minty::UUID::UUID(StringView const &string)
    : m_id(0)
{
	if (string.is_empty())
	{
		return;
	}

	decode_base16(string.get_data(), string.get_size(), m_id, sizeof(Byte) * UUID_BYTE_SIZE);
}

UUID Minty::UUID::create()
{
	UInt64 randomValues[2];
	randomValues[0] = Math::random_ulong();
	randomValues[1] = Math::random_ulong();
	return UUID(reinterpret_cast<Byte const (&)[UUID_BYTE_SIZE]>(randomValues));
}

String Minty::to_string(UUID const obj)
{
	Char buffer[UUID_BYTE_SIZE * 2 + 1];
	encode_base16(obj.get_bytes(), UUID_BYTE_SIZE, buffer, sizeof(buffer));
	buffer[UUID_BYTE_SIZE * 2] = '\0';
	return String(buffer);
}

UUID Minty::parse_to_uuid(String const &string)
{
	UUID value;
	parse_try_uuid(string, value);
	return value;
}

Bool Minty::parse_try_uuid(String const &string, UUID &value)
{
	// check if empty or "NULL"
	if (string.is_empty())
	{
		value = UUID();
		return false;
	}

	if (string == "NULL" || string == "null")
	{
		value = UUID();
		return true;
	}

	// check if the string is a valid UUID
	if (string.get_size() != sizeof(ID) * 2)
	{
		return false;
	}

	value = UUID(string.get_view());
	return true;
}
