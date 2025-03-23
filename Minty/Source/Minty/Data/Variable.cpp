#include "pch.h"
#include "Variable.h"

using namespace Minty;

Bool Minty::Variable::operator==(Variable const& other) const
{
	return m_type == other.m_type && m_data.get_size() == other.m_data.get_size() && memcmp(m_data.get_data(), other.m_data.get_data(), m_data.get_size()) == 0;
}

void Minty::Variable::set_type(Type const type)
{
	MINTY_ASSERT(type < Type::Object, "Cannot set Variable type to an object.");

	clear();
	m_type = type;
}

void Minty::Variable::set_data(void const* const data)
{
	if (data)
	{
		MINTY_ASSERT(m_type != Type::Undefined, "Type is undefined. Cannot set data to non-null.");
		m_data.set(data, sizeof_type(m_type));
	}
	else
	{
		m_data.clear();
	}
}
