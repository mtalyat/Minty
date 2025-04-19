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

void Minty::UUID::serialize(Writer& writer, String const& name) const
{
	writer.write(name, to_string());
}

Bool Minty::UUID::deserialize(Reader& reader, Size const index)
{
	String text;
	if (!reader.read(index, text))
	{
		return false;
	}
	return parse(text);
}

Bool Minty::UUID::parse(String const& text)
{
	if (text.get_size() != sizeof(ID) * 2)
	{
		return false;
	}

	decode_base16(text, &m_id, sizeof(ID));
	return true;
}

String Minty::UUID::to_string() const
{
	return encode_base16(&m_id, sizeof(ID));
}

UUID Minty::UUID::create()
{
    return UUID(uniformDistribution(randomEngine));
}