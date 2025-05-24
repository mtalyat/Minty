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
	Node child(name, data, size, m_allocator);
	return add_child(std::move(child));
}

Node& Minty::Node::add_child(Node const& node)
{
	String const& name = node.get_name();
	MINTY_ASSERT(!m_lookup.contains(name), "Name already exists.");
	Int const index = static_cast<Int>(m_children.get_size());
	m_children.add(node);
	if (!name.is_empty())
	{
		m_lookup[name] = index;
	}
	return m_children.at(index);
}

Node& Minty::Node::add_child(Node&& node)
{
	String const& name = node.get_name();
	MINTY_ASSERT(!m_lookup.contains(name), "Name already exists.");
	Int const index = static_cast<Int>(m_children.get_size());
	if (!name.is_empty())
	{
		m_lookup[name] = index;
	}
	m_children.add(std::move(node));
	return m_children.at(index);
}
