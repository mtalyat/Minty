#include "pch.h"
#include "Node.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Stack.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

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
	Int const index = static_cast<Int>(m_children.get_size());
	if (!name.is_empty() && !m_lookup.contains(name))
	{
		m_lookup[name] = index;
	}
	m_children.add(std::move(node));
	return m_children.at(index);
}

void Minty::Node::serialize(Writer& writer, String const& name) const
{
	// write this value
	writer.write(name, get_data_string());

	// write children
	writer.indent();
	for (auto const& child : m_children)
	{
		child.serialize(writer, child.get_name());
	}
	writer.outdent();
}

Bool Minty::Node::deserialize(Reader& reader, Size const index)
{
	// directly copy the node from the reader to this
	*this = reader.get_node().get_child(index);
	return true;
}

String Minty::to_string(Node const& obj)
{
	MINTY_ABORT("Not implemented.");
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

Node Minty::parse_to_node(String const& string)
{
	// split lines
	Vector<String> lines = string.split_lines();

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

	Stack<Node*> nodeStack;
	nodeStack.push(&root);
	Node* node = nodeStack.peek();

	int const SPACES_PER_TAB = 4;

	// remove all comments from the lines
	Bool inBlockComment = false;
	for (String& line : lines)
	{
		String cleanLine;
		cleanLine.reserve(line.get_size());
		Size i = 0;
		while (i < line.get_size())
		{
			Char c = line.at(i);
			if (inBlockComment)
			{
				if (c == '-' && i + 1 < line.get_size() && line.at(i + 1) == '#')
				{
					inBlockComment = false;
					i += 2;
				}
				else
				{
					i++;
				}
			}
			else if (c == '#' && i + 1 < line.get_size() && line.at(i + 1) == '-')
			{
				inBlockComment = true;
				i += 2;
			}
			else if (c == '#' && i + 1 < line.get_size() && line.at(i + 1) == ' ')
			{
				// single-line comment, skip to end of line
				break;
			}
			else
			{
				cleanLine.append(c);
				i++;
			}
		}
		line = cleanLine;
	}

	Vector<Tuple<String, NodeMacro>> macros;
	for (Size lineIndex = 0; lineIndex < lines.get_size(); lineIndex++)
	{
		String line = lines.at(lineIndex);
		
		// skip empty
		if (line.get_size() == 0)
		{
			continue;
		}

		// read macros or other special lines
		if (line.front() == '#')
		{
			if (line.starts_with("#define"))
			{
				Size nameIndex = 8;

				// find end of name
				Size nameEnd = nameIndex;
				for (; nameEnd < line.get_size(); nameEnd++)
				{
					Char c = line.at(nameEnd);
					if (!isalnum(c) && c != '_')
					{
						break;
					}
				}

				// if end is (, get args

				// get name
				String macroName = line.sub(nameIndex, nameEnd - nameIndex);
				// get macro data
				NodeMacro macro{};
				// if has arguments
				Size valueIndex = nameEnd;
				if (nameEnd < line.get_size() && line.at(nameEnd) == '(')
				{
					// find end of args
					Tuple<Size, Size> argGroup = line.find_group('(', ')', nameEnd);
					MINTY_ASSERT(argGroup.get_first() == nameEnd + 1, "#define found the wrong group.");
					MINTY_ASSERT(argGroup.get_second() != INVALID_INDEX, "#define missing ')'.");

					String argLine = line.sub(argGroup.get_first(), argGroup.get_second());
					macro.parameters = argLine.split(',');
					for (String& param : macro.parameters)
					{
						param = param.trim();
					}

					valueIndex = argGroup.get_first() + argGroup.get_second() + 1;
				}

				// get value
				String value = line.sub(valueIndex + 1, line.get_size() - valueIndex - 1);
				while (value.ends_with("\\"))
				{
					macro.values.add(value.sub(0, value.get_size() - 1));

					lineIndex++;
					if (lineIndex == lines.get_size())
					{
						value = "";
						break;
					}
					value = lines.at(lineIndex);
				}
				if (!value.is_empty())
				{
					macro.values.add(value);
				}

				// add to macros
				macros.add({ macroName, std::move(macro) });
			}

			// skip line if started with #
			continue;
		}

		// replace macros
		Size macroLineNumber = 0;
		Size macroLineCount = 1;
		while (macroLineNumber < macroLineCount)
		{
			String macroLine = lines.at(macroLineNumber + lineIndex);

			Size macroIndex = 0;
			while (macroIndex < macros.get_size())
			{
				auto const& [name, macro] = macros.at(macroIndex);

				Size mStart = macroLine.find_first(name);
				Size mEnd = mStart + name.get_size();

				if (mStart == INVALID_INDEX)
				{
					macroIndex++;
					continue;
				}

				Size count = 0;
				while (mStart != INVALID_INDEX)
				{
					// check if the macro is a valid word, by itself
					if ((mStart != 0 && is_word_character(macroLine.at(mStart - 1))) ||
						(mEnd < macroLine.get_size() && is_word_character(macroLine.at(mEnd))))
					{
						// skip, not the right macro
						mStart = mEnd;
						mStart = macroLine.find_first(name, mStart + 1);
						mEnd = mStart + name.get_size();
						continue;
					}

					Vector<Tuple<String, String>> args;

					// if params, replace those
					if (!macro.parameters.is_empty())
					{
						auto [start, count] = macroLine.find_group('(', ')', mStart + name.get_size());
						MINTY_ASSERT(start != INVALID_INDEX, F("Macro \"{}\" missing its arguments.", name));
						Vector<String> parts = macroLine.sub(start, count).split(',');
						MINTY_ASSERT(parts.get_size() == macro.parameters.get_size(), F("Macro \"{}\" has an incorrect number of arguments.", name));
						for (Size argIndex = 0; argIndex < parts.get_size(); argIndex++)
						{
							args.add({ macro.parameters.at(argIndex), parts.at(argIndex) });
						}
						mEnd = start + count + 1;
					}

					// get text before and after the macro
					String before = macroLine.sub(0, mStart);
					String after = macroLine.sub(mEnd, macroLine.get_size() - mEnd);

					// insert lines and replace args as they are inserted
					Size valueCount = macro.values.get_size();
					for (Size valueIndex = 0; valueIndex < valueCount; valueIndex++)
					{
						// get value
						String value = macro.values.at(valueIndex);

						// replace args
						for (auto const& [find, replace] : args)
						{
							value = value.replace(find, replace);
						}

						// insert before and after as needed
						if (valueIndex == 0)
						{
							value = before + value;
						}
						if (valueIndex == valueCount - 1)
						{
							value = value + after;
						}

						// replace or insert the line
						if (valueIndex == 0)
						{
							// replace line
							lines.at(macroLineNumber + lineIndex) = value;
						}
						else
						{
							// insert a line
							lines.insert(macroLineNumber + lineIndex + valueIndex, value);
							macroLineCount++;
						}
					}

					count++;

					mStart = macroLine.find_first(name, mStart + 1);
					mEnd = mStart + name.get_size();
				}

				if (count)
				{
					// if the macro replaced anything, re-evaluate the line
					macroLineNumber--;
					macroIndex = macros.get_size();
					break;
				}

				macroIndex++;
			}

			macroLineNumber++;
		}

		// re-get line
		line = lines.at(lineIndex);

		// skip empty/whitespace line
		Size solidIndex = line.find_first_not_of(TEXT_WHITESPACE);
		if (solidIndex == INVALID_INDEX)
		{
			continue;
		}

		// if first line starts with a ": ", then that is the data for the root node
		if (line.starts_with(": "))
		{
			String temp = line.sub(2, line.get_size() - 2);
			root.set_data(temp.get_data(), temp.get_size());
			continue;
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
			value = value.replace("\\n", "\n");
		}
		else
		{
			// String::split by colon, if there is one
			Size split = line.find_first(':');

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
				value = value.replace("\\n", "\n");
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
