#include "pch.h"
#include "Node.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Stack.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Tool/String.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

String Minty::Node::get_data_string() const
{
	if (m_data.get_size() == 0)
	{
		return String();
	}

	String text(0, m_data.get_size());
	memcpy(text.get_data(), m_data.get_data(), m_data.get_size());
	return text;
}

Node const &Minty::Node::get_child(Size const index) const
{
	MINTY_ASSERT_F(index < m_children.get_size(), ErrorCode::Argument_OutOfRange, index);
	return m_children[index];
}

Node const &Minty::Node::get_child(String const &name) const
{
	MINTY_ASSERT_F(m_lookup.contains(name), ErrorCode::Argument_KeyNotFound, name);
	return m_children[m_lookup[name]];
}

Node &Minty::Node::add_child(String const &name, AnyConst const data, Size const size)
{
	Node child(name, data, size);
	return add_child(std::move(child));
}

Node &Minty::Node::add_child(Node const &node)
{
	String const &name = node.get_name();
	MINTY_ASSERT_F(!m_lookup.contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
	Int const index = static_cast<Int>(m_children.get_size());
	m_children.add(node);
	if (!name.is_empty())
	{
		m_lookup[name] = index;
	}
	return m_children.at(index);
}

Node &Minty::Node::add_child(Node &&node)
{
	String const &name = node.get_name();
	Int const index = static_cast<Int>(m_children.get_size());
	if (!name.is_empty() && !m_lookup.contains(name))
	{
		m_lookup[name] = index;
	}
	m_children.add(std::move(node));
	return m_children.at(index);
}

Bool Minty::Node::merge(Node const &other)
{
	if (m_name != other.m_name)
	{
		return false;
	}

	// merge data
	m_data = other.m_data;

	// merge children
	for (auto const &otherChild : other.m_children)
	{
		String const &childName = otherChild.get_name();
		if (m_lookup.contains(childName))
		{
			// merge existing child
			Int const index = m_lookup[childName];
			m_children.at(index).merge(otherChild);
		}
		else
		{
			// add new child
			add_child(otherChild);
		}
	}

	return true;
}

struct NodeMacro
{
	Vector<String> parameters;
	Vector<String> values;
};

static Bool is_word_character(Char const c)
{
	return isalnum(c) || c == '_';
}

void Minty::Serializer<Node>::serialize(Writer &writer, Node const &value)
{
	// write the node's data, if any
	if (value.has_data())
	{
		String const dataStr = value.get_data_string();
		if (!dataStr.is_empty())
		{
			writer.write_inline(dataStr);
		}
	}

	// write all children
	for (auto const &child : value.get_children())
	{
		String const& childName = child.get_name();
		String const childData = child.get_data_string();
		writer.indent(childName);
		serialize(writer, child);
		writer.outdent();
	}
}

Bool Minty::Serializer<Node>::deserialize(Reader &reader, Node &value)
{
	String tempName;
	String tempValue;
	Node root;

	// read the root node's value, if any
	if (reader.read_inline(tempValue))
	{
		root.set_data(tempValue.get_data(), tempValue.get_size());
	}

	// working stack to keep track of the current node
	Stack<Node*> nodeStack;

	// start with the root node
	nodeStack.push(&root);

	do
	{
		Node& node = *nodeStack.peek();

		// try to read next key-value pair and indent in case there are more child nodes
		tempValue = "";
		if (reader.indent_next_optional(tempName, tempValue))
		{
			// create and add a child
			node.add_child(Node(tempName, tempValue));

			// add the new child to the operating stack
			nodeStack.push(&node.get_children().back());

			// move on and operate on that child
			continue;
		}

		// if no checks were successful, pop node and continue work on previous node
		nodeStack.pop();

		// if stack is empty, we are done
		if (nodeStack.is_empty())
		{
			break;
		}
		
		// decrease indent after a pop,
		// but only for the non-root nodes
		reader.outdent();

	} while(true);

	value = root;
	return true;
}