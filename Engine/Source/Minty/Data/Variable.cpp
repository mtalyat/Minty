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
			: m_type(type)
			, m_data()
		{
		}

        Minty::Variable::Variable(Type const type, void const *const data)
			: m_type(type)
			, m_data(data, sizeof_type(type))
		{
		}

Bool Minty::Variable::operator==(Variable const &other) const
{
	return m_type == other.m_type && m_data.get_size() == other.m_data.get_size() && memcmp(m_data.get_data(), other.m_data.get_data(), m_data.get_size()) == 0;
}

void Minty::Variable::set_type(Type const type)
{
	MINTY_ASSERT(type < Type::Object, ErrorCode::Argument_InvalidValue, type);

	clear();
	m_type = type;
}

void Minty::Variable::set_data(void const* const data)
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

void Minty::Variable::serialize(Writer& writer, String const& name) const
{
	if (m_data.get_size() == 0)
	{
		// no value
		writer.write(name, m_type);
	}
	else
	{
		// value
		writer.write_typed(name, m_data.get_data(), m_type);
	}
}

Bool Minty::Variable::deserialize(Reader& reader, Size const index)
{
	// make space for data
	m_data.resize(64 * sizeof(Byte));
	if (!reader.read_typed(index, m_data.get_data(), m_type))
	{
		// failed to read data
		m_data.clear();
		return m_type != Type::Undefined;
	}
	// successfully read data
	// scale to proper size
	m_data.resize(sizeof_type(m_type));
	return true;
}
