#include "pch.h"
#include "Variable.h"
#include "Minty/Core/Constant.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

Minty::Variable::Variable()
	: m_type(Type::Undefined)
{
}

Minty::Variable::Variable(Type const type)
	: m_type(type), m_data()
{
}

Minty::Variable::Variable(Type const type, AnyConst const data)
	: m_type(type), m_data(data, sizeof_type(type))
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

void Minty::Variable::set_data(AnyConst const data)
{
	if (data)
	{
		MINTY_ASSERT(m_type != Type::Undefined, ErrorCode::Object_InvalidState);
		m_data.set(data, sizeof_type(m_type));
	}
	else
	{
		m_data.clear();
	}
}

void Minty::Serializer<Variable>::serialize(Writer &writer, Variable const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Variable>::deserialize(Reader &reader, Variable &value)
{
	// read typed data
	Type type;
	Byte buffer[TYPE_MAX_SIZE];
	if(!reader.read_inline(type, buffer))
	{
		// failed to read any data
		value.m_type = Type::Undefined;
		value.m_data.clear();
		return false;
	}

	// set the type and data
	value.set_data(type, buffer);
	return true;
}