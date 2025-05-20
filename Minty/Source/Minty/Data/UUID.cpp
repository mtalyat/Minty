#include "pch.h"
#include "UUID.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include <random>

using namespace Minty;

static std::random_device randomDevice;
static std::mt19937_64 randomEngine(randomDevice());
static std::uniform_int_distribution<Size> uniformDistribution;

UUID Minty::UUID::create()
{
    return UUID(uniformDistribution(randomEngine));
}

String Minty::to_string(UUID const obj)
{
	ID data = obj.get_data();
	return encode_base16(&data, sizeof(ID));
}

UUID Minty::parse_to_uuid(String const& string)
{
	// check if the string is a valid UUID
	if (string.get_size() != sizeof(ID) * 2)
	{
		return UUID();
	}

	ID value;
	decode_base16(string, &value, sizeof(ID));
	return value;
}

Bool Minty::parse_try_uuid(String const& string, UUID& value)
{
	// check if the string is a valid UUID
	if (string.get_size() != sizeof(ID) * 2)
	{
		return false;
	}

	decode_base16(string, &value, sizeof(ID));
	return true;
}
