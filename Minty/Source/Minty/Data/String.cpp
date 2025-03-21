#include "pch.h"
#include "String.h"
#include <cstring>

using namespace Minty;

Minty::String::String(Size const capacity, Allocator const allocator)
	: m_allocator(allocator)
	, m_capacity(0)
	, m_size(0)
	, mp_data(nullptr)
{
	// do nothing if no capacity
	if (capacity == 0)
	{
		return;
	}

	reserve(capacity);
}

Minty::String::String(Char const* const data, Allocator const allocator)
	: m_allocator(allocator)
	, m_capacity(0)
	, m_size(0)
	, mp_data(nullptr)
{
	// do nothing if null
	if (!data)
	{
		return;
	}

	// calculate size
	Char const* ptr = data;
	while (*ptr)
	{
		m_size += 1;
		++ptr;
	}
	m_capacity = m_size;

	// allocate memory
	mp_data = static_cast<Char*>(allocate((m_capacity + 1) * sizeof(Char), m_allocator));
	mp_data[m_capacity] = '\0';
	memcpy(mp_data, data, m_size * sizeof(Char));
}

Minty::String::String(Char const character, Size const count, Allocator const allocator)
	: m_allocator(allocator)
	, m_capacity(0)
	, m_size(0)
	, mp_data(nullptr)
{
	// do nothing if count is zero
	if (count == 0)
	{
		return;
	}

	// allocate memory
	m_capacity = count;
	m_size = count;
	mp_data = static_cast<Char*>(allocate((m_capacity + 1) * sizeof(Char), m_allocator));
	mp_data[m_capacity] = '\0';

	// fill memory with character
	memset(mp_data, character, m_size * sizeof(Char));
}

String Minty::String::operator+(String const& other) const
{
	// handle empty cases
	if (m_size == 0)
	{
		return other;
	}
	else if (other.m_size == 0)
	{
		return *this;
	}

	String result(m_size + other.m_size);
	memcpy(result.mp_data, mp_data, m_size * sizeof(Char));
	memcpy(result.mp_data + m_size * sizeof(Char), other.mp_data, other.m_size * sizeof(Char));
	result.m_size = m_size + other.m_size;
	result.mp_data[result.m_size] = '\0';
	return result;
}

void Minty::String::reserve(Size const capacity)
{
	// update capacity
	m_capacity = capacity;

	// cap size to capacity, if needed
	if (m_size > m_capacity)
	{
		m_size = m_capacity;
	}

	// if new capacity is zero, deallocate all memory
	if (m_capacity == 0)
	{
		if (mp_data)
		{
			delete[] mp_data;
			mp_data = nullptr;
		}
		return;
	}

	// allocate new memory
	Char* newData = static_cast<Char*>(allocate((m_capacity + 1) * sizeof(Char), m_allocator));
	newData[m_size] = '\0';

	// copy over data, if any
	if (mp_data)
	{
		memcpy(newData, mp_data, m_size * sizeof(Char));

		// deallocate old memory
		deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
	}

	// replace memory
	mp_data = newData;
}

void Minty::String::resize(Size const size, Char const value)
{
	// if new size is above capacity, reserve more memory
	if (size > m_capacity)
	{
		reserve(size);
	}

	// in the new space, fill with spaces
	if (size > m_size)
	{
		memset(mp_data + m_size, value , (size - m_size) * sizeof(Char));
	}

	// update size
	m_size = size;

	// update null terminator, if possible
	if (m_capacity > 0)
	{
		mp_data[m_size] = '\0';
	}
}

String& Minty::String::append(String const& other)
{
	// handle empty cases
	if (other.m_size == 0)
	{
		return *this;
	}
	else if (m_size == 0)
	{
		*this = other;
		return *this;
	}

	// reserve space
	Size const newSize = m_size + other.m_size;
	if (newSize > m_capacity)
	{
		if (m_capacity * 2 >= newSize)
		{
			reserve(m_capacity * 2);
		}
		else
		{
			reserve(newSize);
		}
	}

	// copy over data
	memcpy(mp_data + m_size, other.mp_data, other.m_size * sizeof(Char));
	m_size = newSize;
	mp_data[m_size] = '\0';

	return *this;
}

String& Minty::String::append(Char const character)
{
	Size const newSize = m_size + 1;
	if (newSize > m_capacity)
	{
		if (m_capacity * 2 >= newSize)
		{
			reserve(m_capacity * 2);
		}
		else
		{
			reserve(newSize);
		}
	}

	// copy over data
	mp_data[m_size] = character;
	m_size = newSize;
	mp_data[m_size] = '\0';

	return *this;
}

String Minty::String::sub(Size const start, Size const length) const
{
	MINTY_ASSERT(start < m_size, "Start index is out of bounds.");
	MINTY_ASSERT(start + length <= m_size, "Start + length index is out of bounds.");

	// create new string
	String result;
	result.resize(length);
	memcpy(result.mp_data, mp_data + start, length * sizeof(Char));

	return result;
}

Size Minty::String::find(String const& sub, Size const index) const
{
	if (is_empty() || sub.is_empty())
	{
		return INVALID_INDEX;
	}

	Size length = m_size - sub.m_size + 1;
	for (Size i = index; i < length; ++i)
	{
		if (memcmp(mp_data + i, sub.mp_data, sub.m_size * sizeof(Char)) == 0)
		{
			return i;
		}
	}

	return INVALID_INDEX;
}

Size Minty::String::find(Char const character, Size const index) const
{
	if (is_empty() || character == '\0')
	{
		return INVALID_INDEX;
	}

	for (Size i = index; i < m_size; ++i)
	{
		if (mp_data[i] == character)
		{
			return i;
		}
	}

	return INVALID_INDEX;
}

Size Minty::String::find_first_of(String const& sub, Size const index) const
{
	if (is_empty() || sub.is_empty())
	{
		return INVALID_INDEX;
	}
	Size length = m_size;
	for (Size i = index; i < length; ++i)
	{
		for (Size j = 0; j < sub.m_size; ++j)
		{
			if (mp_data[i] == sub.mp_data[j])
			{
				return i;
			}
		}
	}
	return INVALID_INDEX;
}

Size Minty::String::find_first_not_of(String const& sub, Size const index) const
{
	if (is_empty() || sub.is_empty())
	{
		return INVALID_INDEX;
	}
	Size length = m_size;
	for (Size i = index; i < length; ++i)
	{
		Bool found = false;
		for (Size j = 0; j < sub.m_size; ++j)
		{
			if (mp_data[i] == sub.mp_data[j])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			return i;
		}
	}
	return INVALID_INDEX;
}

Bool Minty::String::starts_with(String const& sub) const
{
	if (is_empty() || sub.is_empty())
	{
		return false;
	}
	if (sub.m_size > m_size)
	{
		return false;
	}
	return memcmp(mp_data, sub.mp_data, sub.m_size * sizeof(Char)) == 0;
}

Bool Minty::String::ends_with(String const& sub) const
{
	if (is_empty() || sub.is_empty())
	{
		return false;
	}
	if (sub.m_size > m_size)
	{
		return false;
	}
	return memcmp(mp_data + m_size - sub.m_size, sub.mp_data, sub.m_size * sizeof(Char)) == 0;
}

String Minty::String::to_upper(String const& str)
{
	String copy(str);
	for (Size i = 0; i < str.get_size(); i++)
	{
		Char c = copy.at(i);
		if (c >= 'a' && c <= 'z')
		{
			copy.mp_data[i] = c - 'a' + 'A';
		}
	}
	return copy;
}

String Minty::String::to_lower(String const& str)
{
	String copy(str);
	for (Size i = 0; i < str.get_size(); i++)
	{
		Char c = copy.at(i);
		if (c >= 'A' && c <= 'Z')
		{
			copy.mp_data[i] = c - 'A' + 'a';
		}
	}
	return copy;
}

String Minty::String::replace(String const& str, String const& find, String const& replace)
{
	// find all occurances of the string
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find(find, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += find.get_size();
	}

	// if no occurances, return the original string
	if (indices.is_empty())
	{
		return str;
	}

	// calculate new size
	Size newSize = str.get_size() + indices.get_size() * (replace.get_size() - find.get_size());
	String result(0, newSize);

	// copy over data
	Size offset = 0;
	Size last = 0;
	for (Size i = 0; i < indices.get_size(); i++)
	{
		Size current = indices[i];
		Size length = current - last;
		memcpy(result.mp_data + offset, str.mp_data + last, length * sizeof(Char));
		offset += length;
		memcpy(result.mp_data + offset, replace.mp_data, replace.get_size() * sizeof(Char));
		offset += replace.get_size();
		last = current + find.get_size();
	}

	// copy over the rest of the data
	Size length = str.get_size() - last;
	memcpy(result.mp_data + offset, str.mp_data + last, length * sizeof(Char));

	return result;
}

Vector<String> Minty::String::split(String const& str, Char const delimiter)
{
	Vector<String> result;

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find(delimiter, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += 1;
	}

	// if no occurances, return the original string
	if (indices.is_empty())
	{
		result.add(str);
		return result;
	}

	// calculate new size
	result.reserve(indices.get_size() + 1);

	// copy over data
	Size last = 0;
	for (Size i = 0; i < indices.get_size(); i++)
	{
		Size current = indices[i];
		Size length = current - last;
		result.add(str.sub(last, length));
		last = current + 1;
	}

	// copy over the rest of the data
	Size length = str.get_size() - last;
	result.add(str.sub(last, length));
	return result;
}

Vector<String> Minty::String::split(String const& str, String const& delimiter)
{
	Vector<String> result;

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find(delimiter, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += delimiter.get_size();
	}

	// if no occurances, return the original string
	if (indices.is_empty())
	{
		result.add(str);
		return result;
	}

	// calculate new size
	result.reserve(indices.get_size() + 1);

	// copy over data
	Size last = 0;
	for (Size i = 0; i < indices.get_size(); i++)
	{
		Size current = indices[i];
		Size length = current - last;
		result.add(str.sub(last, length));
		last = current + delimiter.get_size();
	}

	// copy over the rest of the data
	Size length = str.get_size() - last;
	if (length > 0)
	{
		result.add(str.sub(last, length));
	}
	return result;
}

std::ostream& Minty::operator<<(std::ostream& stream, String const& str)
{
	if (str.mp_data)
	{
		stream << str.mp_data;
	}
	return stream;
}
