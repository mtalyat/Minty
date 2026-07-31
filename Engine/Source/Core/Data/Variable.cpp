#include "pch.hpp"
#include "Variable.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

Minty::Variable::Variable()
	: m_type(TypeEnum::Undefined)
{
}

Minty::Variable::Variable(Type const type)
	: m_type(type), m_data()
{
}

Minty::Variable::Variable(Type const type, PointerConst const data)
	: m_type(type), m_data(data, type.get_size())
{
}

Bool Minty::Variable::operator==(Variable const &other) const
{
	return m_type == other.m_type && m_data.get_size() == other.m_data.get_size() && memcmp(m_data.get_data(), other.m_data.get_data(), m_data.get_size()) == 0;
}

void Minty::Variable::set_type(Type const type)
{
	clear();
	m_type = type;
}

void Minty::Variable::set_data(PointerConst const data)
{
	if (data)
	{
		MINTY_ASSERT(m_type != TypeEnum::Undefined, ErrorCodeEnum::Object_InvalidState);
		m_data.set(data, m_type.get_size());
	}
	else
	{
		m_data.clear();
	}
}

Bool Minty::Serializer<Variable>::serialize(Writer &writer, Variable const &value)
{
	MINTY_NOT_IMPLEMENTED();
	return Bool();
}

Bool Minty::Serializer<Variable>::deserialize(Reader &reader, Variable &value)
{
	// read typed data
	TypeEnum type;
	Byte buffer[TYPE_MAX_SIZE]; // max size of any type
	if(!reader.read_primary("Type", type, buffer))
	{
		// failed to read any data
		value.m_type = TypeEnum::Undefined;
		value.m_data.clear();
		return false;
	}

	// set the type and data
	value.set_type(type);
	value.set_data(buffer);
	return true;
}