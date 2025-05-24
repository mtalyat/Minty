#include "pch.h"
#include "Node.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Stack.h"

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

String Minty::to_string(Node const& obj)
{
	MINTY_ABORT("Not implemented.");
}

Node Minty::parse_to_node(String const& string)
{
	// split lines
	Vector<String> lines = String::split(string, "\n");

	// parse node
	int indent = 0;
	String key;
	String value;

	Node root;

	// if no lines, node is empty
	if (lines.is_empty())
	{
		return root;
	}

	// if first line starts with a ": ", then that is the data for the root node
	if (lines.front().starts_with(": "))
	{
		String temp = lines.front().sub(2, lines.front().get_size() - 2);
		root.set_data(temp.get_data(), temp.get_size());
	}

	Stack<Node*> nodeStack;
	nodeStack.push(&root);
	Node* node = nodeStack.peek();

	int const SPACES_PER_TAB = 4;

	Map<String, String> macros;

	for (String line : lines)
	{
		// read macros or other special lines
		if (line.front() == '#')
		{
			if (line.starts_with("#define"))
			{
				// remove "#define "
				line = line.sub(7, line.get_size() - 7); // remove "#define "

				// skip whitespace
				Size solidIndex = line.find_first_not_of(" \t\n\v\f\r");
				line = line.sub(solidIndex, line.get_size() - solidIndex);

				// split into name and value
				Size index = line.find(' ');
				String macroName = line.sub(0, index);
				String macroValue = line.sub(index + 1, line.get_size() - index - 1);

				MINTY_ASSERT(!macroName.is_empty(), "Macro name is empty.");

				// define macro
				macros[macroName] = macroValue;
			}
			continue;
		}

		// skip empty/whitespace/comment lines
		Size solidIndex = line.find_first_not_of(" \t\n\v\f\r");
		if (line.get_size() == 0 || solidIndex == INVALID_INDEX || line.front() == '#' || line.front() == ':')
		{
			continue;
		}

		// replace macros
		for (auto const& macro : macros)
		{
			line = String::replace(line, macro.get_first(), macro.get_second());
		}

		// count number of tabs (indents)

		int spaces = 0;
		for (char const c : line)
		{
			if (c == ' ')
			{
				// add once space
				spaces += 1;
			}
			else if (c == '\t')
			{
				// multiple sapces
				spaces += SPACES_PER_TAB;
			}
			else
			{
				// done
				break;
			}
		}
		int i = spaces / SPACES_PER_TAB;

		int indentChange = i - indent;

		// if new indent is too deep, ignore
		if (indentChange > 1)
		{
			MINTY_WARNING(F("Discarding line, invalid indent change of {}: {}", indentChange, line));
			continue;
		}

		// check change in index
		if (indentChange > 0)
		{
			nodeStack.push(&node->get_children().back());

			// start using that as active node
			node = nodeStack.peek();

			// update indent
			indent = i;
		}
		else if (indentChange < 0)
		{
			// going down, so pop down X nodes, where X is the difference between indents
			for (; indentChange < 0; indentChange++)
			{
				nodeStack.pop();
			}

			// update node reference
			node = nodeStack.peek();

			// update indent
			indent = i;
		}

		// remove indents for parsing
		if (spaces > 0)
		{
			line = line.sub(solidIndex, line.get_size() - solidIndex);
		}

		if (line.starts_with("- "))
		{
			// bullet point, use "" as key and the whole line as the value
			key = "";
			value = line.sub(2, line.get_size() - 2);
			value = String::replace(value, "\\n", "\n");
		}
		else
		{
			// String::split by colon, if there is one
			Size split = line.find(':');

			if (split == INVALID_INDEX)
			{
				// no String::split, just key
				key = line;
				value = "";
			}
			else
			{
				// String::split: implies key: value
				key = line.sub(0, split);
				// ignore ": "
				Size size = line.get_size() - split - 2;
				if (split < line.get_size() - 2)
				{
					// something on other side of ": "
					value = line.sub(split + 2, size);
				}
				else
				{
					// nothing on other side of the ": "
					value = "";
				}
				value = String::replace(value, "\\n", "\n");
			}
		}

		// get index of newNode
		Size index = node->get_children().get_size();

		// add node to children
		node->add_child(key, value);
	}

	return root;
}

Bool Minty::parse_try_node(String const& string, Node& value)
{
	MINTY_ABORT("Not implemented.");
	return Bool();
}
