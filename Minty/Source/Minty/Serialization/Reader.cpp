#include "pch.h"
#include "Reader.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/UUID.h"
#include "Minty/Serialization/Serializable.h"
#include "Minty/Serialization/SerializableObject.h"

using namespace Minty;

void* Minty::Reader::get_user_data() const
{
	if (m_dataStack.get_size() == 0)
	{
		return nullptr;
	}

	return m_dataStack.peek();
}

void Minty::Reader::push_user_data(void* const data)
{
	m_dataStack.push(data);
}

void Minty::Reader::pop_user_data()
{
	MINTY_ASSERT(m_dataStack.get_size() > 0, "Data stack is empty.");

	m_dataStack.pop();
}

Bool Minty::Reader::read_object(Size const index, SerializableObject& obj)
{
	if (indent(index))
	{
		Bool result = obj.deserialize(*this);
		outdent();
		return result;
	}

	return false;
}

Bool Minty::Reader::read_asset(Size const index, Ref<Asset>& asset)
{
	UUID id{};
	if (read(index, id))
	{
		// if ID is empty, that is okay, set to null
		if (!id.is_valid())
		{
			asset = nullptr;
			return true;
		}

		AssetManager& assetManager = AssetManager::get_singleton();
		asset = assetManager.get_asset(id);
		if (asset == nullptr)
		{
			// if ID not invalid, and no asset found, error
			MINTY_ERROR(F("Failed to read Asset with ID {}. It has not been loaded.", id));
			return false;
		}

		// asset found and set
		return true;
	}

	// no ID read
	return false;
}

void Minty::FileReaderBehavior::read_data(void* const data, Size const size)
{
	MINTY_ASSERT(mp_file != nullptr, "File is null.");
	MINTY_ASSERT(mp_file->is_open(), "File is not open.");

	mp_file->read(data, size);
}

Vector<Byte> Minty::FileReaderBehavior::read_all()
{
	Vector<Byte> fileData;
	fileData.resize(mp_file->get_size(), 0);
	read_data(fileData.get_data(), fileData.get_size());
	return fileData;
}

void Minty::MemoryReaderBehavior::read_data(void* const data, Size const size)
{
	// read from current index
	Byte* memoryData = static_cast<Byte*>(mp_data->get_data());
	memcpy(data, &memoryData[m_index], size);

	// incremement position
	m_index += size;
}

Vector<Byte> Minty::MemoryReaderBehavior::read_all()
{
	// save position
	Size index = m_index;
	m_index = 0;

	// read all data
	Vector<Byte> memoryData;
	memoryData.resize(mp_data->get_size(), 0);
	read_data(memoryData.get_data(), memoryData.get_size());

	// set position back
	m_index = index;

	return memoryData;
}

Node Minty::TextReaderBehavior::read_node(const void* const data, Size const size) const
{
	// get contents of file as text for parsing
	Vector<Char> contents;
	contents.resize(size + 1, 0);
	contents[size] = 0; // set 0 at the end for good measure
	memcpy(contents.get_data(), data, size);

	// get string
	String text(contents.get_data());

	// split lines
	Vector<String> lines = String::split(text, "\n");

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

	for (String line : lines)
	{
		// skip empty/whitespace/comment lines
		Size solidIndex = line.find_first_not_of(" \t\n\v\f\r");
		if (line.get_size() == 0 || solidIndex == INVALID_INDEX || line.front() == '#' || line.front() == ':')
		{
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


Bool Minty::TextReaderBehavior::read_bool_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_bool(text);
}
Bool2 Minty::TextReaderBehavior::read_bool2_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_bool2(text);
}
Bool3 Minty::TextReaderBehavior::read_bool3_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_bool3(text);
}
Bool4 Minty::TextReaderBehavior::read_bool4_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_bool4(text);
}
Char Minty::TextReaderBehavior::read_char_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_char(text);
}
Byte Minty::TextReaderBehavior::read_byte_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_byte(text);
}
Short Minty::TextReaderBehavior::read_short_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_short(text);
}
UShort Minty::TextReaderBehavior::read_ushort_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_ushort(text);
}
Int Minty::TextReaderBehavior::read_int_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_int(text);
}
Int2 Minty::TextReaderBehavior::read_int2_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_int2(text);
}
Int3 Minty::TextReaderBehavior::read_int3_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_int3(text);
}
Int4 Minty::TextReaderBehavior::read_int4_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_int4(text);
}
UInt Minty::TextReaderBehavior::read_uint_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_uint(text);
}
UInt2 Minty::TextReaderBehavior::read_uint2_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_uint2(text);
}
UInt3 Minty::TextReaderBehavior::read_uint3_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_uint3(text);
}
UInt4 Minty::TextReaderBehavior::read_uint4_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_uint4(text);
}
Long Minty::TextReaderBehavior::read_long_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_long(text);
}
ULong Minty::TextReaderBehavior::read_ulong_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_ulong(text);
}
Float Minty::TextReaderBehavior::read_float_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_float(text);
}
Float2 Minty::TextReaderBehavior::read_float2_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_float2(text);
}
Float3 Minty::TextReaderBehavior::read_float3_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_float3(text);
}
Float4 Minty::TextReaderBehavior::read_float4_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_float4(text);
}
Double Minty::TextReaderBehavior::read_double_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return to_double(text);
}
String Minty::TextReaderBehavior::read_string_from_buffer(const void* const data, Size const size) const
{
	if (!size) return "";

	Vector<Char> text;
	text.resize(size + 1, 0);
	memcpy(text.get_data(), data, sizeof(Char) * size);
	text.at(size) = '\0';
	return String(text.get_data());
}

UUID Minty::TextReaderBehavior::read_uuid_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	UUID id = parse_to_uuid(text);
	return id;
}

Type Minty::TextReaderBehavior::read_type_from_buffer(const void* const data, Size const size) const
{
	if (!size) return {};

	String text = read_string_from_buffer(data, size);
	return parse_to_type(text);
}

void* Minty::TextReaderBehavior::read_typed_from_buffer(const void* const data, Size const size, Type const type) const
{
	if (!size) return nullptr;

	void* output;
	Size outputSize = sizeof_type(type);

	switch (type)
	{
	case Type::Bool:
	{
		auto temp = read_bool_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Bool2:
	{
		auto temp = read_bool2_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Bool3:
	{
		auto temp = read_bool3_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Bool4:
	{
		auto temp = read_bool4_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Char:
	{
		auto temp = read_char_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Byte:
	{
		auto temp = read_byte_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Short:
	{
		auto temp = read_short_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::UShort:
	{
		auto temp = read_ushort_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Int:
	{
		auto temp = read_int_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Int2:
	{
		auto temp = read_int2_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Int3:
	{
		auto temp = read_int3_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Int4:
	{
		auto temp = read_int4_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::UInt:
	{
		auto temp = read_uint_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::UInt2:
	{
		auto temp = read_uint2_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::UInt3:
	{
		auto temp = read_uint3_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::UInt4:
	{
		auto temp = read_uint4_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Long:
	{
		auto temp = read_long_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::ULong:
	case Type::Size:
	{
		auto temp = read_ulong_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Float:
	{
		auto temp = read_float_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Float2:
	{
		auto temp = read_float2_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Float3:
	{
		auto temp = read_float3_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Float4:
	{
		auto temp = read_float4_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Double:
	{
		auto temp = read_double_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::String:
	{
		auto temp = read_string_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	case Type::Object:
	{
		auto temp = read_uuid_from_buffer(data, size);
		output = new Byte[outputSize];
		memcpy(output, &temp, outputSize);
	}
	break;
	default:
		MINTY_ABORT(F("Cannot read_bytes type \"{}\".", to_string(type)).get_data());
	}

	return output;
}