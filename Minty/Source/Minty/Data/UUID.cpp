#include "pch.h"
#include "UUID.h"
#include "Minty/Core/Encoding.h"
#include <random>

using namespace Minty;

static std::random_device randomDevice;
static std::mt19937_64 randomEngine(randomDevice());
static std::uniform_int_distribution<Size> uniformDistribution;

void Minty::UUID::serialize(Writer& writer, String const& name) const
{
	writer.write(name, to_string(*this));
}

Bool Minty::UUID::deserialize(Reader& reader, Int const index)
{
	String text;
	if (!reader.read(index, text))
	{
		return false;
	}
	decode_base16(text, &m_id, sizeof(ID));
	return true;
}

UUID Minty::UUID::create()
{
    return UUID(uniformDistribution(randomEngine));
}

String Minty::to_string(UUID const value)
{
	ID id = value.get_data();
	return encode_base16(&id, sizeof(ID));
}