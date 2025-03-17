#include "pch.h"
#include "Node.h"

using namespace Minty;

String Minty::Node::get_data_string() const
{
	if (m_data.get_size() == 0)
	{
		return String();
	}

	String text(0, m_data.get_size(), m_allocator);
	memcpy(text.get_data(), m_data.get_data(), m_data.get_size());
	return text;
}

Node& Minty::Node::add_child(String const& name, void const* const data, Size const size)
{
	MINTY_ASSERT(!name.is_empty(), "Name cannot be empty.");
	MINTY_ASSERT(!m_lookup.contains(name), "Name already exists.");

	Node child(name, data, size, m_allocator);
	Int const index = static_cast<Int>(m_children.get_size());
	m_children.add(child);
	m_lookup[name] = index;
	return m_children.at(index);
}
