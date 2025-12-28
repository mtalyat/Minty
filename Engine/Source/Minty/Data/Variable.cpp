#include "pch.h"
#include "Variable.h"
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
	MINTY_ASSERT_F(type < Type::Object, ErrorCode::Argument_InvalidValue, type);

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

void Minty::ItemSerializer<Variable>::serialize_item(Writer &writer, StringView const name, Variable const &value)
{
	if (value.is_empty())
	{
		// just the type
		writer.write_type(name, value.get_type());
	} else
	{
		// typed data
		writer.write_typed(name, value.get_data().get_data(), value.get_type());
	}
}

void Minty::ItemSerializer<Variable>::deserialize_item(Reader &reader, Size const index, Variable &value)
{
	// read typed data
	value.m_data.resize(64 * sizeof(Byte));
	if (!reader.read_typed(index, value.m_data.get_data(), value.m_type))
	{
		// failed to read data
		value.m_data.clear();
		return;
	}
	// successfully read data
	// scale down to proper size
	value.m_data.resize(sizeof_type(value.m_type));
}