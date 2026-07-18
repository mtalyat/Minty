#include "pch.hpp"
#include "UUID.hpp"
#include "Core/Encoding/Encoding.hpp"
#include "Core/Math/Random.hpp"

using namespace Minty;

Minty::UUID::UUID()
	: m_data(0)
{
}

Minty::UUID::UUID(Byte const (&id)[BYTE_SIZE])
	: m_data(0)
{
	for (Size i = 0; i < BYTE_SIZE; ++i)
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

UUID Minty::UUID::generate()
{
	UInt64 randomValues[2] = {
		Math::random_ulong(),
		Math::random_ulong()};

	return UUID(reinterpret_cast<Byte const(&)[BYTE_SIZE]>(randomValues));
}

UUID Minty::UUID::from_string(StringView const str)
{
	UUID uuid;
	if (!Parser<UUID>::parse(str, uuid))
	{
		MINTY_ERROR_A(ErrorCodeEnum::Argument_InvalidFormat, str.get_data());
		return UUID();
	}
	return uuid;
}

void Minty::UUID::clear()
{
	std::memset(m_data, 0, BYTE_SIZE);
}

Bool Minty::Parser<UUID>::parse(StringView const str, UUID &value)
{
	// check if empty
	if (str.is_empty())
	{
		return false;
	}

	// check if null (zero)
	if (str == "NULL" || str == "null")
	{
		value.clear();
		return true;
	}

	// check if the string is a valid UUID
	switch (str.get_size())
	{
	case UUID::HEX_SIZE_FULL: // full UUID string
		decode_base16(str.get_data(), str.get_size(), value.m_data, sizeof(Byte) * UUID::BYTE_SIZE);
		break;
	case UUID::HEX_SIZE_HALF: // half UUID string
		std::memset(value.m_data + UUID::BYTE_SIZE_HALF, 0, UUID::BYTE_SIZE_HALF);
		decode_base16(str.get_data(), str.get_size(), value.m_data, UUID::BYTE_SIZE_HALF);
		break;
	default: // invalid size
		return false;
	}

	return true;
}

String Minty::Parser<UUID>::to_string(UUID const &value)
{
	// if the high bits are zero, return the short version
	if (*static_cast<UInt64 const *>(static_cast<void const *>(value.m_data + UUID::BYTE_SIZE_HALF)) == 0)
	{
		Char buffer[UUID::HEX_SIZE_HALF + 1];
		encode_base16(value.m_data, UUID::BYTE_SIZE_HALF, buffer, sizeof(buffer));
		buffer[UUID::HEX_SIZE_HALF] = '\0';
		return String(buffer);
	}
	else
	{
		Char buffer[UUID::HEX_SIZE_FULL + 1];
		encode_base16(value.m_data, UUID::BYTE_SIZE, buffer, sizeof(buffer));
		buffer[UUID::HEX_SIZE_FULL] = '\0';
		return String(buffer);
	}
}
